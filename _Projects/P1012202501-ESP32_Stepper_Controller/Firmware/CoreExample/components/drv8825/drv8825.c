/*
* DRV8825 interface for ESP32 source file
* drv8825.c
* Michael Dawson
* michaelshanedawson@gmail.com
*
* v0.0.1
*/

#include "drv8825.h"
#include "../systemstatus/systemstatus.h"
#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_clk_tree.h"
#include "soc/clk_tree_defs.h"
#include "driver/gpio.h"
#include  "driver/ledc.h"

/*variables for the DRV8825 system*/
const int STP_ENABLE = 14; // GPIO pin used for enabling the IC, active LOW, must be LOW for driver to operate
const int STP_RESET = 13; // GPIO pin used for reset pin on the IC, active LOW
const int STP_DIR = 5; // Direction control pin for the IC
const int STP_STEP = 12; // GPIO pin for the step input of the IC
const int STP_MS0 = 15; // GPIO pin used for Microstep Mode 0
const int STP_MS1 = 16; // GPIO pin used for Microstep Mode 1
const int STP_MS2 = 17; // GPIO pin used for Microstep Mode 2
const int STP_FAULT = 18; // GPIO pin used to detect a fault condition on the IC, active LOW, generic fault condition

/*GPIO Output Pins*/
int DRV8825_GPIO_OUTPUT_PINS[] = {STP_ENABLE, STP_RESET, STP_DIR, STP_MS0, STP_MS1, STP_MS2};
int DRV8825_GPIO_OUTPUT_PINS_DEFAULT_LEVEL[] = {1, 0, 0, 1, 1, 1}; 

/*GPIO Input Pins*/
int DRV8825_GPIO_INPUT_PINS[] = {STP_FAULT};

/*Define prototypes*/
void DRV8825_INIT();
static void drv8825_task();
void DRV8825_STOP();
void DRV8825_START();
void DRV8825_RESET();
void DRV8825_DIRECTION(uint8_t dir);
void DRV8825_SPEED(uint8_t spd);



void DRV8825_STOP()
{
    gpio_set_level(STP_ENABLE, 1);
    gpio_set_level(STP_RESET, 0);     
}

void DRV8825_START()
{
    gpio_set_level(STP_RESET, 1);
    gpio_set_level(STP_ENABLE, 0);
    
}

void DRV8825_DIRECTION(uint8_t dir)
{
    gpio_set_level(STP_DIR, dir);
}

void DRV8825_SPEED(uint8_t spd)
{
    STP_DUTY = spd;
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, STP_DUTY); //Set the new duty cycle value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); //Perform the duty cycle update
}

/*Here we will configure the GPIO inputs and outputs for the stepper driver IC*/
void DRV8825_INIT()
{
    /*Configure GPIO INPUT pins*/    
    uint8_t i = 0;
    for(i = 0; i < (sizeof(DRV8825_GPIO_INPUT_PINS) / sizeof(DRV8825_GPIO_INPUT_PINS[0])); i++)
    {
        gpio_reset_pin(DRV8825_GPIO_INPUT_PINS[i]);
        gpio_set_direction(DRV8825_GPIO_INPUT_PINS[i], GPIO_MODE_INPUT);
    }   

    /*Configure GPIO OUTPUT pins*/
    for(i = 0; i < (sizeof(DRV8825_GPIO_OUTPUT_PINS) / sizeof(DRV8825_GPIO_OUTPUT_PINS[0])); i++)
    {
        gpio_reset_pin(DRV8825_GPIO_OUTPUT_PINS[i]);
        gpio_set_direction(DRV8825_GPIO_OUTPUT_PINS[i], GPIO_MODE_OUTPUT);
        gpio_set_level(DRV8825_GPIO_OUTPUT_PINS[i], DRV8825_GPIO_OUTPUT_PINS_DEFAULT_LEVEL[i]);
    }

    /*Configure the LEDC PWM system parameters*/
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_8_BIT, //Resolution of the PWM duty        
        .freq_hz = 10000,                  //PWM Frequency
        .speed_mode = LEDC_LOW_SPEED_MODE,    //Timer Mode - LS only for the ESP32-C3
        .timer_num = LEDC_TIMER_0,            //Timer Index
        .clk_cfg = LEDC_USE_APB_CLK             //Auto select the clock source
    };
    
    /*Sets the configuration for the LEDC timer*/
    ledc_timer_config(&ledc_timer); 

    /*Configure the LEDC PWM channel*/
    ledc_channel_config_t ledc_channel = {
        .channel = LEDC_CHANNEL_0,
        .duty = 0,
        .gpio_num = STP_STEP,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_0
    };

    /*Sets the LEDC controller with the channel configuration information*/
    ledc_channel_config(&ledc_channel);

    /*The LEDC PWM should be operational at this moment with a 0% duty cycle. We will set it to an updated value as designated in PWM_DUTY*/
    //PWM_DUTY = PWM_DUTY * 100; //Convert the percentage to a useable duty cycle for the driver
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, STP_DUTY); //Set the new duty cycle value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); //Perform the duty cycle update


    //xTaskCreate(drv8825_task, "drv8825_task", 1024 * 2, NULL, 1, NULL);
}



static void drv8825_task()
{
    /*The LEDC PWM should be operational at this moment with a 0% duty cycle. We will set it to an updated value as designated in PWM_DUTY*/
    //PWM_DUTY = PWM_DUTY * 100; //Convert the percentage to a useable duty cycle for the driver
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, STP_DUTY); //Set the new duty cycle value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); //Perform the duty cycle update

    uint8_t faultDetected = gpio_get_level(STP_FAULT); //The pin will go LOW if a fault is detected
    if(STP_FAULT != 1)
    {
        STATUS_BYTE = (1 & 0x8); //General DRV8825 fault condition exists, generic detection only
    }
    vTaskDelay(25 / portTICK_PERIOD_MS);   
}
