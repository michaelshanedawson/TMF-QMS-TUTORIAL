#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "../components/systemstatus/systemstatus.h"
#include "../components/pwmfan/pwmfan.h"
#include "../components/uartconsole/uartconsole.h"
#include "../components/rs485/rs485.h"
#include "../components/drv8825/drv8825.h"
#include "../components/nvssystem/nvssystem.h"
#include "../components/tmp3x/tmp3x.h"

/*Variables for the DRV8825 IC*/
uint8_t STP_DUTY = 2; // 0 to 100 duty cycle input from main code to drive the stepper motor using LEDC, default is 0

/* Variables for the PWM fan*/
uint8_t FAN_PWM_PIN = 23; //Output pin for the fan PWM control
uint8_t FAN_TACH_PIN = 22; //Fan tachometer input pin, most designs use an open collector that relies on a pull-up resistor
uint8_t FAN_PULSE_PER_REV = 2; //How many pulses the fan generates per full revolution, each fan could be different, check datasheets

/*Variables for the UART Console*/
uint8_t UART_RX_PIN = 19; // GPIO pin used for the UART RX
uint8_t UART_TX_PIN = 21; // GPIO pin used for the UART TX
uint32_t BAUD_RATE = 115200; // Baud rate for UART communication
char* delimiter = " "; // Delimiter for input parsing

/*Variables for RS485 Interface*/
uint8_t RS485_RX_PIN = 25; // GPIO pin used for the UART RX
uint8_t RS485_TX_PIN = 26; // GPIO pin used for the UART TX
uint8_t RS485_DIR_CONTROL = 27;
uint32_t RS485_BAUD_RATE = 115200; // Baud rate for UART communication
char* RS485_delimiter = " "; // Delimiter for input parsing

/*Variables for the system status interface*/
uint8_t STATUS_LED_PIN = 4; //GPIO pin of the integrated red LED on the PCB

/*Variables for the NVS system*/
int32_t CYCLE_COUNT = 0;

/*Varaibles for the temperature sensor, tmp3x*/
uint8_t TMP3X_PIN = 2; //This is the analog pin the sensor is tied to for readings

/*System Operating Variables*/
const int LIMIT_1 = 35; //GPIO pin of LIMIT SWITCH 1 - INPUT ONLY, Right Hand Side
uint8_t LIMIT_1_STATUS = 0;
const int LIMIT_2 = 36; //GPIO pin of LIMIT SWITCH 2 - INPUT ONLY, Left Hand Side
uint8_t LIMIT_2_STATUS = 0;
const int LIMIT_3 = 39; //GPIO pin of LIMIT SWITCH 3 - INPUT ONLY, Not used in this example here for reference only
uint8_t LIMIT_3_STATUS = 0;

const int CONTROL_1 = 32; //GPIO pin of CONTROL INPUT 1 - INPUT ONLY
uint8_t CONTROL_1_STATUS = 0;
const int CONTROL_2 = 33; //GPIO pin of CONTROL INPUT 2 - INPUT ONLY, Not used in this example here for reference only
uint8_t CONTROL_2_STATUS = 0;
const int CONTROL_3 = 34; //GPIO pin of CONTROL INPUT 3 - INPUT ONLY, Not used in this example here for reference only
uint8_t CONTROL_3_STATUS = 0;

int GPIO_INPUTS[] = {LIMIT_1, LIMIT_2, LIMIT_3, CONTROL_1, CONTROL_2, CONTROL_3};

bool TRAVEL_DIRECTION = 0; // 0 or 1, handles checking for our gantry movement
bool IS_OPERATING = 0;

/*System Operating Prototypes*/



void app_main(void)
{    
    /*Configure GPIO INPUT pins*/    
    uint8_t i = 0;
    for(i = 0; i < (sizeof(GPIO_INPUTS) / sizeof(GPIO_INPUTS[0])); i++)
    {
        gpio_reset_pin(GPIO_INPUTS[i]);
        gpio_set_direction(GPIO_INPUTS[i], GPIO_MODE_INPUT);
    }


    /*Initialize the PWM Fan Driver*/
    fan_init(FAN_PWM_PIN, FAN_TACH_PIN, FAN_PULSE_PER_REV, 0); //Start the fan PWM driver on the proper pin and the initial default PWM value

    /*Initialize the UART Interface Driver for Debugging*/
    //uartconsole_init(UART_RX_PIN, UART_TX_PIN, BAUD_RATE, delimiter);
    //uartconsole_send("\033[H\033[J");
    //uartconsole_send("UART Interface Online!\n");
    //uartconsole_send("-------------------\n\n");

    /*Initialize the RS485 Interface*/
    //RS485_init(RS485_RX_PIN, RS485_TX_PIN, RS485_BAUD_RATE, RS485_DIR_CONTROL, RS485_delimiter);
    //RS485_send("\033[H\033[J");
    //RS485_send("RS485 Interface Online\n");
    //RS485_send("-------------------\n\n");

    /*Initialize the NVS system*/
    nvs_init();

    /*Intialize the DRV8825 IC and set default PWM value, typically 0*/
    DRV8825_INIT();
    DRV8825_STOP();

    /*Initialize the tmp3x system*/
    tmp3x_init();

    /*Initialize the system status functions*/
    status_init();

   
    while(1)
    {
        CONTROL_1_STATUS = gpio_get_level(CONTROL_1);
        CONTROL_2_STATUS = gpio_get_level(CONTROL_2);
        CONTROL_3_STATUS = gpio_get_level(CONTROL_3);

        LIMIT_1_STATUS = gpio_get_level(LIMIT_1);
        LIMIT_2_STATUS = gpio_get_level(LIMIT_2);
        LIMIT_3_STATUS = gpio_get_level(LIMIT_3);

        if((CONTROL_1_STATUS != 0) && (STATUS_BYTE == 0)) //Only proceed if the enable button is engaged and the system status is NO_FAULT
        {
            //RS485_send("Enable is good.\n");
            if(IS_OPERATING == 0)
            {
                DRV8825_START();
                IS_OPERATING = 1;
            }

            /*Secondary safety check, if both limit switches fail then the system will stop and flag errors*/
            if((LIMIT_1_STATUS != 1) && (LIMIT_2_STATUS != 1))
            {
                /*This will eventually become an error flag that can be monitored*/
                //RS485_send("Both Limit Switches Disconnected!\n");
                STATUS_BYTE = (1 & 0x1);
                DRV8825_STOP();
            }

            /*This is our main operating section of the system*/
            else
            {
                STATUS_BYTE = (0 & 0x1);
                if(LIMIT_1_STATUS != 1) //Indicates left side, stepper is CW rotation or dir of 1
                {                     
                    if(TRAVEL_DIRECTION == 1)
                    {
                        DRV8825_STOP();
                        TRAVEL_DIRECTION = 0;
                        DRV8825_DIRECTION(TRAVEL_DIRECTION);
                        DRV8825_START();
                        CYCLE_COUNT ++;                         
                    }         
                }
                
                else if(LIMIT_2_STATUS != 1) //Indicated right side, stepper is CCW rotation or dir of 0
                {
                    if(TRAVEL_DIRECTION == 0)
                    {
                        DRV8825_STOP();
                        TRAVEL_DIRECTION = 1;
                        DRV8825_DIRECTION(TRAVEL_DIRECTION);
                        DRV8825_START();
                    }
                }
            }
        }

        else if(CONTROL_1_STATUS == 0)
        {
            if(IS_OPERATING == 1)
            {
                DRV8825_STOP();
                IS_OPERATING = 0;
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

