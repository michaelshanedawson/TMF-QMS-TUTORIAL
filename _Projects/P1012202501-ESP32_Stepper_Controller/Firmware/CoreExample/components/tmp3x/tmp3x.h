/*
* tmp3x.h
* Michael Dawson
* michaelshanedawson@gmail.com
*
* Header file for the Analog Devices TMP3x series of low voltage temp sensors on the ESP32.
*
* V0.0.1
*/

#ifndef tmp3x_H
#define tmp3x_H

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

//Variable declarations
extern uint8_t TMP3X_PIN;
extern float TEMPERATURE;


void tmp3x_init();



#ifdef __cplusplus
}
#endif

#endif // tmp3x_H