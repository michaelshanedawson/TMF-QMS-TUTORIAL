#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../components/uartconsole/uartconsole.h"

uint8_t UART_RX_PIN = 19; // GPIO pin used for the UART RX
uint8_t UART_TX_PIN = 21; // GPIO pin used for the UART TX
uint32_t BAUD_RATE = 115200; // Baud rate for UART communication
char* delimiter = " "; // Delimiter for input parsing


void app_main(void)
{
    uartconsole_init(UART_RX_PIN, UART_TX_PIN, BAUD_RATE, delimiter);
    uartconsole_send("\033[H\033[J");
    uartconsole_send("P1012202501 UART FTDI Interface Test Firmware.\n");
    uartconsole_send("-------------------\n\n");
    
    while(1)
    {
        ;
    }
}


