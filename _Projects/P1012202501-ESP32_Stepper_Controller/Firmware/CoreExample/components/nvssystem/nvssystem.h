/*
* nvssystem.h
* Michael Dawson
* michaelshanedawson@gmail.com
*
* Header file for the basic NVS system for the ESP32.
*
* V0.0.1
*/

#ifndef nvssystem_H
#define nvssystem_H

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
extern int32_t CYCLE_COUNT;

void nvs_init();
void nvs_read();
void nvs_write();
void nvs_clear();
void nvs_fan_write();



#ifdef __cplusplus
}
#endif

#endif // nvssystem_H