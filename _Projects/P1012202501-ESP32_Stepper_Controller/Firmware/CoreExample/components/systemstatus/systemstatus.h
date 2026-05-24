/*
* systemstatus.h
* Michael Dawson
* michaelshanedawson@gmail.com
*
* Header file for the basic system status for the ESP32.
*
* V0.0.1
*/

#ifndef systemstatus_H
#define systemstatus_H

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
extern uint8_t STATUS_LED_PIN;
extern unsigned char STATUS_BYTE;
extern int8_t IS_FAN_INSTALLED;
extern bool IS_IN_ERROR;

void status_init();



#ifdef __cplusplus
}
#endif

#endif // systemstatus_H