/*
*   
*   
*   main.c
*   Author: Mike Dawson
*   Date: 8/6/2024
*   Version: 0.1
*   See README.md for complete changelog
*
*   This system utilizes the LED PWM driver API from the ESP IDF to define the stepper speed.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_clk_tree.h"
#include "soc/clk_tree_defs.h"
#include "esp_mac.h"

/* GPIO pin definitions xx GPIO total, xx used so far */
const int STEPPER_FAULT = 18; //
int GPIO_INPUTS[] = {STEPPER_FAULT};

const int STEPPER_ENABLE_PIN = 14; //This is an output, active HIGH IO14 default
const int STEPPER_DIRECTION = 5; //This is an output, level determines direction of the stepper motor
const int MICROSTEP_0 = 15; //
const int MICROSTEP_1 = 16; //
const int MICROSTEP_2 = 17; //
const int STP_RESET = 13; //
int GPIO_OUTPUTS[] = {STEPPER_ENABLE_PIN, STEPPER_DIRECTION, MICROSTEP_0, MICROSTEP_1,
                      MICROSTEP_2, STP_RESET};
int GPIO_OUTPUTS_DEFAULT_LEVEL[] = {1, 0, 1, 1, 1, 1}; //Default is Counter-Clockwise

/* Stepper drive definitions */
uint8_t STEPPER_STEP = 12;
uint32_t PWM_DUTY = (50); // 2,4,6,8,10 @ 40000Hz


void app_main(void)
{
    printf("Entered main task.\n");

    /*Configure GPIO INPUT pins*/    
    uint8_t i = 0;
    for(i = 0; i < (sizeof(GPIO_INPUTS) / sizeof(GPIO_INPUTS[0])); i++)
    {
        gpio_reset_pin(GPIO_INPUTS[i]);
        gpio_set_direction(GPIO_INPUTS[i], GPIO_MODE_INPUT);
    }   

    /*Configure GPIO OUTPUT pins*/
    for(i = 0; i < (sizeof(GPIO_OUTPUTS) / sizeof(GPIO_OUTPUTS[0])); i++)
    {
        gpio_reset_pin(GPIO_OUTPUTS[i]);
        gpio_set_direction(GPIO_OUTPUTS[i], GPIO_MODE_OUTPUT);
        gpio_set_level(GPIO_OUTPUTS[i], GPIO_OUTPUTS_DEFAULT_LEVEL[i]);
    }
    

    /*Configure the LEDC PWM system parameters*/
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_4_BIT, //Resolution of the PWM duty        
        .freq_hz = 20000,                  //PWM Frequency
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
        .gpio_num = STEPPER_STEP,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_0
    };

    /*Sets the LEDC controller with the channel configuration information*/
    ledc_channel_config(&ledc_channel);

    /*The LEDC PWM should be operational at this moment with a 0% duty cycle. We will set it to an updated value as designated in PWM_DUTY*/
    //PWM_DUTY = PWM_DUTY * 100; //Convert the percentage to a useable duty cycle for the driver
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, PWM_DUTY); //Set the new duty cycle value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); //Perform the duty cycle update

    while(1)
    {
        gpio_set_level(STEPPER_DIRECTION, 0); //Set direction to Counter-Clockwise rotation
        vTaskDelay(50 / portTICK_PERIOD_MS);
        gpio_set_level(STEPPER_ENABLE_PIN, 0);//Enable the stepper motor
        gpio_set_level(STP_RESET, 1);         //Reset the internal system
        vTaskDelay(10000 / portTICK_PERIOD_MS);        
        gpio_set_level(STEPPER_ENABLE_PIN, 1); //Shut down the stepper motor
        gpio_set_level(STP_RESET, 0); //Reset the internal system
        vTaskDelay(50 / portTICK_PERIOD_MS);
        gpio_set_level(STEPPER_DIRECTION, 1); //Set direction to Clockwise rotation
        vTaskDelay(50 / portTICK_PERIOD_MS);
        gpio_set_level(STEPPER_ENABLE_PIN, 0); //Enable the stepper motor
        gpio_set_level(STP_RESET, 1); //Deassert reset
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

