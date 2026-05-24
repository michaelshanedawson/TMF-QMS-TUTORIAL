/*
* TMP3x Temperature Sensor for ESP32 source file
* tmp3x.c
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
adc_cali_handle_t cali_handle = NULL;

static int adc_raw[1][10];
static int voltage;
float TEMPERATURE = 0.0;

/*Define prototypes*/
void tmp3x_init();
void temperature_monitor_task();

/* This is where we will add any custom code to read the temperature data*/
void tmp3x_init()
{
    /*ADC Unit 1 Init*/    
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
    
    adc_cali_create_scheme_line_fitting(&cali_config, &cali_handle);

    xTaskCreate(temperature_monitor_task, "temp_task", 1024 * 2, NULL, 2, NULL);
}

void temperature_monitor_task()
{
    while(1)
    {
        adc_oneshot_read(adc1_handle, ADC_CHAN, &adc_raw[0][0]);
        adc_cali_raw_to_voltage(cali_handle, adc_raw[0][0], &voltage);
        TEMPERATURE = (((int)voltage) - 750.00) / 10 + 25;
        vTaskDelay(50 / portTICK_PERIOD_MS);    
    }
}




