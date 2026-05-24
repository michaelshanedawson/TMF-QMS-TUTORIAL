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
#include "../drv8825/drv8825.h"

/*Variables*/
unsigned char STATUS_BYTE = 0;
int8_t IS_FAN_INSTALLED = 0; //To indicate if we are using the optional fan, 0 is no fan and 1 is fan installed. 0 is default.
bool IS_IN_ERROR = 0;
bool IS_FAN_RUNNING = 0;
float FAN_ON_LOW_TEMP = 40.0; //The first temperature the fan will kick on in low speed mode, 40°C
float FAN_ON_HIGH_TEMP = 85.0; //The absolute warmest we want the DRV8825 IC to reach, 85°C
int FAN_LOW_SPEED = 50; //50% speed
int FAN_HIGH_SPEED = 100; //100% speed



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
        if((STATUS_BYTE != 0) || (IS_IN_ERROR != 0))
        {
            gpio_set_level(STATUS_LED_PIN, 1);
            DRV8825_STOP();
        }

        else
        {
            gpio_set_level(STATUS_LED_PIN, 0);
        }

        if(TEMPERATURE < (FAN_ON_LOW_TEMP - 10))
        {
            fan_set(0);
            IS_FAN_RUNNING = 0;
        }

        if((TEMPERATURE > FAN_ON_LOW_TEMP) && (TEMPERATURE < FAN_ON_HIGH_TEMP))
        {
            fan_set(FAN_LOW_SPEED);
            IS_FAN_RUNNING = 1;
        }

        if(TEMPERATURE > FAN_ON_HIGH_TEMP)
        {
            fan_set(FAN_HIGH_SPEED);
            IS_FAN_RUNNING = 1;
        }

        if((IS_FAN_INSTALLED != 0) && (IS_FAN_RUNNING != 0))
        {
            uint32_t fanRPM = get_fan_rpm();
            if(fanRPM < 2)
            {
                STATUS_BYTE |= (1U << 4);
                IS_IN_ERROR = 1;
                
            }
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);    
    }
}


