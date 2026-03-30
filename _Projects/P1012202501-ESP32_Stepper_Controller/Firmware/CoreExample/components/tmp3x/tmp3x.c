/*
* System Status for ESP32 source file
* systemstatus.c
* Michael Dawson
* michaelshanedawson@gmail.com
*
* v0.0.1
*/

#include "tmp3x.h"
#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
/*Additional systems we need access to*/
#include "../rs485/rs485.h"


#define ADC_CHAN                ADC_CHANNEL_4
#define ADC_ATTEN               ADC_ATTEN_DB_12
#define ADC_BITWIDTH            ADC_BITWIDTH_12

adc_oneshot_unit_handle_t adc1_handle;
adc_cali_handle_t handle = NULL;

static int adc_raw[1][10];
static int voltage[1][10];


double voltageConverted = 0.0;
float TEMPERATURE = 0.0;

#define WINDOW_SIZE 10

int buffer[WINDOW_SIZE]; //Stores the last N samples
int bufferindex = 0; //Current write position
int count = 0; //How many samples have been added (up to N)
int sum = 0; //Running SUM of samples
int voltageValue = 0;
int averageVoltage = 0;


/*Define prototypes*/
void tmp3x_init();
void temperature_monitor_task();

/* This is where we will add any custom code to read the temperature data*/
void tmp3x_init()
{
    for (int i = 0; i < WINDOW_SIZE; i++)
    {
        buffer[i] = 0;
    }

    /*ADC Unit 2 Init*/
    
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };

    adc_oneshot_new_unit(&init_config1, &adc1_handle);

    /*ADC Unit 2 Config*/
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH,
        .atten = ADC_ATTEN,
    };

    adc_oneshot_config_channel(adc1_handle, ADC_CHAN, &config);

    
    adc_cali_line_fitting_config_t cali_config = {
            .unit_id = ADC_UNIT_1,
            .atten = ADC_ATTEN,
            .bitwidth = ADC_BITWIDTH,
        };
    
    adc_cali_create_scheme_line_fitting(&cali_config, &handle);

    xTaskCreate(temperature_monitor_task, "temp_task", 1024 * 2, NULL, 2, NULL);
}

void temperature_monitor_task()
{
    while(1)
    {
        //RS485_send("Temp Task Looping\n");
        adc_oneshot_read(adc1_handle, ADC_CHAN, &adc_raw[0][0]);
        adc_cali_raw_to_voltage(handle, adc_raw[0][0], &voltage[0][0]);
        voltageValue = adc_raw[0][0];
        //printf("ADC Value: %u \n", voltageValue);

        char response[256];
        snprintf(response, sizeof(response), "ADC Value is: %d\n", voltageValue);
        //RS485_send(response);

        //Subtract value being overwritten
        sum -= buffer[bufferindex];
        //Store the new value
        buffer[bufferindex] = voltageValue;
        //Add the new value to the SUM
        sum += voltageValue;
        //Move the index forward in a circular manner
        bufferindex = (bufferindex + 1) % WINDOW_SIZE;
        //Increase count until full
        if(count < WINDOW_SIZE)
        {
            count++;
        }
        averageVoltage = sum/count;

        //TEMPERATURE = (averageVoltage - 500) / 100;
        TEMPERATURE = adc_raw[0][0];

        vTaskDelay(25 / portTICK_PERIOD_MS);    
    }
}




