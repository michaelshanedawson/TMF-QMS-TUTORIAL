#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

#define ADC_CHAN                ADC_CHANNEL_2
#define ADC_ATTEN               ADC_ATTEN_DB_12
#define ADC_BITWIDTH            ADC_BITWIDTH_12

static int adc_raw[1][10];

static int voltage[1][10];
double voltageConverted = 0.0;



void app_main(void)
{
    /*ADC Unit 2 Init*/
     adc_oneshot_unit_handle_t adc1_handle;
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_2,
    };

    adc_oneshot_new_unit(&init_config1, &adc1_handle);

    /*ADC Unit 2 Config*/
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH,
        .atten = ADC_ATTEN,
    };

    adc_oneshot_config_channel(adc1_handle, ADC_CHAN, &config);

    adc_cali_handle_t handle = NULL;
    adc_cali_line_fitting_config_t cali_config = {
            .unit_id = ADC_UNIT_2,
            .atten = ADC_ATTEN,
            .bitwidth = ADC_BITWIDTH,
        };
    
    adc_cali_create_scheme_line_fitting(&cali_config, &handle);

    uint32_t adcValue = 0;
    uint32_t voltageValue = 0;   

    

    while(1)
    {
        adc_oneshot_read(adc1_handle, ADC_CHAN, &adc_raw[0][0]);
        adcValue = adc_raw[0][0];
        printf("ADC Value: %lu \n", adcValue);
        adc_cali_raw_to_voltage(handle, adc_raw[0][0], &voltage[0][0]);
        voltageValue = voltage[0][0];
        printf("Voltage: %lu \n\n", voltageValue);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

