#include <stdio.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED 4

void app_main(void)
{
    /*Configure GPIO pins*/
    gpio_reset_pin(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_level(LED, 0);
    

    while(1)
    {
        gpio_set_level(LED, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);     
    }
}

