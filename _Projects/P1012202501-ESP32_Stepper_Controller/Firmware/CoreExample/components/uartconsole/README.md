# UART FTDI Interface driver for ESP32
This is a lightweight, modular C driver for interfacing ESP32-based microcontrollers to a basic UART console interface using a standard 
FTDI interface cable.

## Features 
*   Bare metal UART and command processing ( no dependency on Arduino layer)
*   Modular header/source structure for easy inclusion

## Folder Structure
/components/uartconsole
├── uartconsole.h        # Public API for external use
├── uartconsole.c        # Core implementation
├── LICENSE.md      # License information
└── README.md       # This file

## Dependencies
* ESP32 SDK (ESD-IDF, Arduino or VSCode)
* UART Number 1
* FreeRTOS 

## Configuration
* Place the pwmfan folder inside of the project components folder
* In the main application C file, include the uartconsole.h file
* UART_RX_PIN for the UART RX, 19 is the default
* UART_TX_PIN for the UART TX, 21 is the default
* BAUD_RATE for the UART baud rate, 115200 is the default
* delimiter used for input parsing, a single space " " is the default, can be set to any valid char
* Recommend disabling any watchdog in the ESP32 for basic use

## Documentation
* uartconsole_init()    Function to initialize the UART module
* uartconsole_send()    Function to send data over the UART lines
* uartconsole_rx_task() Function that handles reading the UART RX buffer and handles the data parsing
