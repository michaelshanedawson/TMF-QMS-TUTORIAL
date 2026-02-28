/*
* rs485.h
* Michael Dawson
* michaelshanedawson@gmail.com
*
* Header file for a basic UART console interface for the ESP32.
*
* V0.0.1
*/

#ifndef rs485_H
#define rs485_H

#include <stdint.h>     // For uint8_t type
#include <stdio.h>      // For printf
#include <stddef.h>     // For size_t
#include <stdlib.h>     // For malloc, free
#include <string.h>     // For memset, memcpy
#include <inttypes.h>   // For PRIx64, etc.   
#include <stdbool.h>    // For bool type
#include <limits.h>     // For INT_MAX, etc.
#include "driver/uart.h"    
#include "freertos/FreeRTOS.h"      
#include "freertos/task.h"  
#include "esp_log.h"    
#include "esp_system.h" 
#include "esp_err.h"  

#ifdef __cplusplus
extern "C" {
#endif

//Variable declarations
extern uint8_t RS485_RX_PIN ; // GPIO pin used for the UART RX
extern uint8_t RS485_TX_PIN ; // GPIO pin used for the UART TX
extern uint32_t RS485_BAUD_RATE; // Baud rate for UART communication
extern uint8_t RS485_DIR_CONTROL; // Direction control pin for the RS485 half duplex IC
extern char RS485_prompt[32]; // Prompt string for the console
extern char* RS485_delimiter; // Delimiter for input parsing

/**
 * @brief Initialize the ESP32 UART console.
 * @param RS485_RX_PIN Pin used for the UART RX
 * @param RS485_TX_PIN Pin used for the UART TX
 * @param RS485_BAUD_RATE Baud rate for UART communication
 * @param RS_485_DIR_CONTROL RS485 Half-Duplex direction control
 * @param RS485_delimiter Delimiter for input parsing
 */

void RS485_init(uint8_t RS485_RX_PIN, uint8_t RS485_TX_PIN, uint32_t RS485_BAUD_RATE, uint8_t RS485_DIR_CONTROL, char* RS485_delimiter);


void RS485_send(const char* data);



#ifdef __cplusplus
}
#endif

#endif // rs485_H