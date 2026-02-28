/*
* System Status for ESP32 source file
* systemstatus.c
* Michael Dawson
* michaelshanedawson@gmail.com
*
* v0.0.1
*/

#include "systemstatus.h"
#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*Additional systems we need access to*/
#include "../pwmfan/pwmfan.h"
#include "../tmp3x/tmp3x.h"

/*Variables*/
unsigned char STATUS_BYTE = 0;



/*Define prototypes*/
void status_init();
void status_monitor_task();

/* This is where we will add any custom code to process terminal commands and provide any feedback*/
void status_init()
{ 
    gpio_reset_pin(STATUS_LED_PIN);
    gpio_set_direction(STATUS_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(STATUS_LED_PIN, 0);

    xTaskCreate(status_monitor_task, "monitor_task", 1024 * 2, NULL, 2, NULL);
}

void status_monitor_task()
{
    while(1)
    {
        if(STATUS_BYTE != 0)
        {
            gpio_set_level(STATUS_LED_PIN, 1);
        }

        else
        {
            gpio_set_level(STATUS_LED_PIN, 0);
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);    
    }
}


