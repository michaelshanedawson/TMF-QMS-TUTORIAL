/*
* drv8825.h
* Michael Dawson
* michaelshanedawson@gmail.com
*
* Header file for the DRV8825 stepper driver IC interface for the ESP32.
*
* V0.0.1
*/

#ifndef drv8825_H
#define drv8825_H

#include <stdint.h>     // For uint8_t type
#include <stdio.h>      // For printf
#include <stddef.h>     // For size_t
#include <stdlib.h>     // For malloc, free
#include <string.h>     // For memset, memcpy
#include <inttypes.h>   // For PRIx64, etc.   
#include <stdbool.h>    // For bool type
#include <limits.h>     // For INT_MAX, etc.
#include "freertos/FreeRTOS.h"      
#include "freertos/task.h"  
#include "esp_log.h"    
#include "esp_system.h" 
#include "esp_err.h"


#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t STP_DUTY; //Stepper motor duty cycle
extern uint8_t STEPPER_ENABLE; //Control the enable line
extern uint8_t STEPPER_RESET; //Control the reset line
extern uint8_t STEPPER_DIRECTION; //Control the direction pin

/**
 * @brief Initialize the DRV8825 IC control task.
 * @param NULL No parameters yet

 */
void DRV8825_INIT();
void DRV8825_STOP();
void DRV8825_START();
void DRV8825_RESET();
void DRV8825_DIRECTION(uint8_t dir);
void DRV8825_SPEED(uint8_t spd);



#ifdef __cplusplus
}
#endif

#endif // drv8825_H