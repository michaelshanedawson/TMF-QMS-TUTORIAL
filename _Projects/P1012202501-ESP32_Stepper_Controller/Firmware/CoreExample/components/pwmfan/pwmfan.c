/*
* pwm fan driver source file
* pwmfan.c
* Michael Dawson
* michaelshanedawson@gmail.com
*
* v0.0.1
*/

#include "pwmfan.h"
#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/pulse_cnt.h"


#define PCNT_HIGH_LIMIT 10000
#define PCNT_LOW_LIMIT -10000

int PULSE_COUNT = 0;

uint32_t FAN_PWM_DUTY = 0; //Maximum is 8192 for 13bit PWM settings
uint32_t FAN_RPM = 0; //The current RPM value of the fan

pcnt_channel_handle_t pcnt_chan_a = NULL;
pcnt_unit_handle_t pcnt_unit = NULL;


/*Define prototypes*/
void fan_init(uint8_t pwm_pin, uint8_t tach_pin, uint8_t pulse_per, uint8_t pwm_value);
long map(long x, long in_min, long in_max, long out_min, long out_max);
void fan_set(uint8_t pwm_value);
uint32_t get_fan_rpm();

void fan_init(uint8_t pwm_pin, uint8_t tach_pin, uint8_t pulse_per, uint8_t pwm_value)
{
    FAN_PWM_DUTY = map(pwm_value, 0, 100, 0, 8192);
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, //Resolution of the PWM duty
        .freq_hz = 5000,                  //PWM Frequency
        .speed_mode = LEDC_LOW_SPEED_MODE,    //Timer Mode - LS only for the ESP32-C3
        .timer_num = LEDC_TIMER_1,            //Timer Index
        .clk_cfg = LEDC_AUTO_CLK             //Auto select the clock source
    };
    
    /*Sets the configuration for the LEDC timer*/
    ledc_timer_config(&ledc_timer); 

    /*Configure the LEDC PWM channel*/
    ledc_channel_config_t ledc_channel = {
        .channel = LEDC_CHANNEL_2,
        .duty = 0,
        .gpio_num = FAN_PWM_PIN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_1
    };

    /*Sets the LEDC controller with the channel configuration information*/
    ledc_channel_config(&ledc_channel);
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, FAN_PWM_DUTY); //Set the new duty cycle value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2); //Perform the duty cycle update
    
    /*Configure the pulse counter module*/
    pcnt_unit_config_t unit_config = {
        .high_limit = PCNT_HIGH_LIMIT,
        .low_limit = PCNT_LOW_LIMIT,
        .intr_priority = 0,
    };
    
    pcnt_new_unit(&unit_config, &pcnt_unit);

    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 1000,
    };
    pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config);

     pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = FAN_TACH_PIN,
        .level_gpio_num = -1,
    };
    
    pcnt_new_channel(pcnt_unit, &chan_a_config, &pcnt_chan_a);

    pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_HOLD, PCNT_CHANNEL_EDGE_ACTION_INCREASE);

    
}

void fan_set(uint8_t pwm_value)
{
    FAN_PWM_DUTY = map(pwm_value, 0, 100, 0, 8192);
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, FAN_PWM_DUTY); //Set the new duty cycle value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2); //Perform the duty cycle update 
}

uint32_t get_fan_rpm()
{    
    pcnt_unit_enable(pcnt_unit);
    pcnt_unit_clear_count(pcnt_unit);
    pcnt_unit_start(pcnt_unit);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    pcnt_unit_disable(pcnt_unit);
    pcnt_unit_get_count(pcnt_unit, &PULSE_COUNT);    
    FAN_RPM = (PULSE_COUNT / FAN_PULSE_PER_REV) * 60;
    return FAN_RPM;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;    
}
