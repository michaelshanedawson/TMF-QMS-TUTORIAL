/*
* pwmfan.h
* Michael Dawson
* michaelshanedawson@gmail.com
*
* Header file for 4 pin PWM fan control. Can also read the tach on a 3 pin fan.
*
* V0.0.1
*/

#ifndef pwmfan_H
#define pwmfan_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//Variable declarations
extern uint8_t FAN_PWM_VALUE; // 0 to 100 range. 0 is full off and 100 is full on
extern uint8_t FAN_PWM_PIN; //Output pin for the fan PWM control
extern uint8_t FAN_TACH_PIN; //Fan tachometer input pin, most designs use an open collector that relies on a pull-up resistor
extern uint8_t FAN_PULSE_PER_REV; //How many pulses the fan generates per full revolution, each fan could be different, check datasheets
extern uint32_t FAN_RPM; //The current RPM value of the fan

/**
 * @brief Initialize the ESP32 PWM on one channel.
 * @param pwm_pin Pin used for the PWM drive output
 * @param pwm_value Initial value for the PWM system
 */

void fan_init(uint8_t pwm_pin, uint8_t tach_pin, uint8_t pulse_per, uint8_t pwm_value);

void fan_set(uint8_t pwm_value);

uint32_t get_fan_rpm();



#ifdef __cplusplus
}
#endif

#endif // pwmfan_H