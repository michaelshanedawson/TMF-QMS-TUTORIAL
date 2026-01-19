#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

const int LED = 4;

const int lmt1 = 35;
const int lmt2 = 36;
const int lmt3 = 39;

const int ctl1 = 32;
const int ctl2 = 33;
const int ctl3 = 34;

int GPIO_INPUTS[] = {lmt1, lmt2, lmt3, ctl1, ctl2, ctl3};


void app_main(void)
{
     /*Configure GPIO INPUT pins*/    
    uint8_t i = 0;
    for(i = 0; i < (sizeof(GPIO_INPUTS) / sizeof(GPIO_INPUTS[0])); i++)
    {
        gpio_reset_pin(GPIO_INPUTS[i]);
        gpio_set_direction(GPIO_INPUTS[i], GPIO_MODE_INPUT);
    }
    
    /*Configure LED GPIO*/
    gpio_reset_pin(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_level(LED, 0);

    while(1)
    {
        if (gpio_get_level(lmt1) == 1)
        {
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }

        if (gpio_get_level(lmt2) == 1)
        {
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);            
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }

        if (gpio_get_level(lmt3) == 1)
        {
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);                        
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }

        if (gpio_get_level(ctl1) == 1)
        {
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);                                       
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }

        if (gpio_get_level(ctl2) == 1)
        {
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);                                       
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }

        if (gpio_get_level(ctl3) == 1)
        {
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);                                        
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }

        else gpio_set_level(LED, 0);
    }
}

