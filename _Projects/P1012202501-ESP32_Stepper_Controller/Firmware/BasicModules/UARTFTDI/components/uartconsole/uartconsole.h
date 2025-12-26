/*
* uartconsole.h
* Michael Dawson
* michaelshanedawson@gmail.com
*
* Header file for a basic UART console interface for the ESP32.
*
* V0.0.1
*/

#ifndef uartconsole_H
#define uartconsole_H

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
extern uint8_t UART_RX_PIN ; // GPIO pin used for the UART RX
extern uint8_t UART_TX_PIN ; // GPIO pin used for the UART TX
extern uint32_t BAUD_RATE; // Baud rate for UART communication
extern char uartconsole_prompt[32]; // Prompt string for the console
extern char* delimiter; // Delimiter for input parsing

/**
 * @brief Initialize the ESP32 UART console.
 * @param UART_RX_PIN Pin used for the UART RX
 * @param UART_TX_PIN Pin used for the UART TX
 * @param BAUD_RATE Baud rate for UART communication
 * @param delimiter Delimiter for input parsing
 */

void uartconsole_init(uint8_t UART_RX_PIN, uint8_t UART_TX_PIN, uint32_t BAUD_RATE, char* delimiter);


void uartconsole_send(const char* data);



#ifdef __cplusplus
}
#endif

#endif // uartconsole_H