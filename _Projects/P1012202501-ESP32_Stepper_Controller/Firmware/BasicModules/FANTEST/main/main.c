#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../components/pwmfan/pwmfan.h"
#include "../components/uartconsole/uartconsole.h"

/* Variables for the PWM fan*/
uint8_t FAN_PWM_PIN = 23; //Output pin for the fan PWM control
uint8_t FAN_TACH_PIN = 22; //Fan tachometer input pin, most designs use an open collector that relies on a pull-up resistor
uint8_t FAN_PULSE_PER_REV = 2; //How many pulses the fan generates per full revolution, each fan could be different, check datasheets

/*Variables for the UART Console*/
uint8_t UART_RX_PIN = 19; // GPIO pin used for the UART RX
uint8_t UART_TX_PIN = 21; // GPIO pin used for the UART TX
uint32_t BAUD_RATE = 115200; // Baud rate for UART communication
char* delimiter = " "; // Delimiter for input parsing

void app_main(void)
{
    fan_init(FAN_PWM_PIN, FAN_TACH_PIN, FAN_PULSE_PER_REV, 0); //Start the fan PWM driver on the proper pin and the initial default PWM value
    uartconsole_init(UART_RX_PIN, UART_TX_PIN, BAUD_RATE, delimiter);
    uartconsole_send("\033[H\033[J");
    uartconsole_send("P1012202501 Fan Test V1.0\n");
    uartconsole_send("-------------------\n\n");

    while(0)
    {
        uint32_t fanspeed = get_fan_rpm();
        printf("Fan RPM is:  %lu \n", fanspeed);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

