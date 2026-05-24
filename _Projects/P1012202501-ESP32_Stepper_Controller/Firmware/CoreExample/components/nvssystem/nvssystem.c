/*
* NVS system for ESP32 source file
* nvssystem.c
* Michael Dawson
* michaelshanedawson@gmail.com
*
* v0.0.1
*/

#include "nvssystem.h"
#include "../systemstatus/systemstatus.h"
#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

/*Define variables*/
nvs_handle_t my_handle;
uint8_t NVS_ERROR = 0;
int32_t PRIOR_CYCLES = 0;

/*Define prototypes*/
void nvs_init();
void nvssystem_task(void *pvParameters);
void nvs_read();
void nvs_write();
void nvs_clear();

void nvs_fan_write();

/* This is where we will itialize the NVS system on the ESP32*/
void nvs_init()
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    nvs_read();
    PRIOR_CYCLES = CYCLE_COUNT;    
    xTaskCreate(nvssystem_task, "nvs_task", 2048, NULL, 5, NULL);
}

void nvssystem_task(void *pvParameters)
{    
    while(1)
    {
        //RS485_send("nvssystem task tick \n");        
        if(CYCLE_COUNT == (PRIOR_CYCLES + 10))
        {
            PRIOR_CYCLES = CYCLE_COUNT; 
            nvs_write();
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);        
    }
}

void nvs_read()
{
    NVS_ERROR = nvs_open("storage", NVS_READWRITE, &my_handle);    
    if(NVS_ERROR != 0)
    {
        /*Error flag handler for the actual NVS system*/
        STATUS_BYTE |= (1U << 2); //Cannot open the storage device
    }

    else
    {
        NVS_ERROR = nvs_get_i32(my_handle, "cycles", &CYCLE_COUNT);        
        switch (NVS_ERROR)
        {
            case 0:
            /*Error flagging control if the NVS is working ok*/
            break;
            case 2:
            /*Error indicating that the value is not found*/
            STATUS_BYTE |= (1U << 3);; //Cannot locate the correct key
            nvs_close(my_handle);
            nvs_write();
            break;
            default:
            /*Error indicating that the data could not be read*/
            break;
        }

         NVS_ERROR = nvs_get_i8(my_handle, "fan", &IS_FAN_INSTALLED);        
        switch (NVS_ERROR)
        {
            case 0:
            /*Error flagging control if the NVS is working ok*/
            break;
            case 2:
            /*Error indicating that the value is not found*/
            STATUS_BYTE |= (1U << 3);; //Cannot locate the correct key
            nvs_close(my_handle);
            nvs_fan_write();
            break;
            default:
            /*Error indicating that the data could not be read*/
            break;
        }

        nvs_close(my_handle);
    }
}

void nvs_write()
{
    NVS_ERROR = nvs_open("storage", NVS_READWRITE, &my_handle);    
    if(NVS_ERROR != 0)
    {
        /*Error flag handler for the actual NVS system*/
        STATUS_BYTE |= (1U << 2); //Cannot open the storage device
    }
    else
    {
        NVS_ERROR = nvs_set_i32(my_handle, "cycles", CYCLE_COUNT);
        nvs_commit(my_handle);
        nvs_close(my_handle);
    }
}

void nvs_fan_write()
{
    NVS_ERROR = nvs_open("storage", NVS_READWRITE, &my_handle);    
    if(NVS_ERROR != 0)
    {
        /*Error flag handler for the actual NVS system*/
        STATUS_BYTE |= (1U << 2); //Cannot open the storage device
    }
    else
    {
        NVS_ERROR = nvs_set_i8(my_handle, "fan", IS_FAN_INSTALLED);
        nvs_commit(my_handle);
        nvs_close(my_handle);
    }    
}

void nvs_clear()
{
    NVS_ERROR = nvs_open("storage", NVS_READWRITE, &my_handle);    
    if(NVS_ERROR != 0)
    {
        /*Error flag handler for the actual NVS system*/
        STATUS_BYTE |= (1U << 2); //Cannot open the storage device
    }
    else
    {
        NVS_ERROR = nvs_set_i32(my_handle, "cycles", 0);
        nvs_commit(my_handle);
        nvs_close(my_handle);
    }
}    





