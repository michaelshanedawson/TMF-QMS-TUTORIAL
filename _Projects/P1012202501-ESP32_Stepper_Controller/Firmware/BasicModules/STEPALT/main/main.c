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
#include "driver/rmt.h"

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
int GPIO_OUTPUTS_DEFAULT_LEVEL[] = {0, 0, 1, 1, 1, 1}; //Default is Counter-Clockwise

/* Stepper drive definitions */
uint8_t STEPPER_STEP = 12;
uint32_t PWM_DUTY = (30); // 2,4,6,8,10 @ 40000Hz

#define RMT_CHANNEL RMT_CHANNEL_0


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

    // Configure RMT for step pulses
    rmt_config_t config = {
        .rmt_mode = RMT_MODE_TX,
        .channel = RMT_CHANNEL,
        .gpio_num = STEPPER_STEP,
        .clk_div = 80, // 1µs per tick (80MHz / 80)
        .mem_block_num = 1,
        .tx_config = {
            .loop_en = false,
            .carrier_en = false,
            .idle_output_en = true,
            .idle_level = RMT_IDLE_LEVEL_LOW
        }
    };
    rmt_config(&config);
    rmt_driver_install(RMT_CHANNEL, 0, 0);

     // Create a pulse pattern: HIGH for 500µs, LOW for 500µs
    rmt_item32_t pulse_item = {
        .duration0 = 500, .level0 = 1,
        .duration1 = 500, .level1 = 0
    };

    // Send 200 steps
    for (int i = 0; i < 2000; i++) {
        rmt_write_items(RMT_CHANNEL, &pulse_item, 1, true);
    }


   

    while(0)
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

