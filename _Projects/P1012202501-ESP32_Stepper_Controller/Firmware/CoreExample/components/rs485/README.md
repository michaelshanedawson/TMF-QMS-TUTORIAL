# RS485 UART Interface driver for ESP32
This is a lightweight, modular C driver for interfacing ESP32-based microcontrollers to a basic RS485 transceiver.

## Features 
*   Bare metal UART and command processing ( no dependency on Arduino layer)
*   Modular header/source structure for easy inclusion

## Folder Structure
/components/rs485
├── rs485.h        # Public API for external use
├── rs485.c        # Core implementation
├── LICENSE.md     # License information
└── README.md      # This file

## Dependencies
* ESP32 SDK (ESD-IDF, Arduino or VSCode)
* UART Number 0
* FreeRTOS 

## Configuration
* Place the pwmfan folder inside of the project components folder
* In the main application C file, include the rs485.h file
* RS485_RX_PIN for the UART RX, 25 is the default
* RS485_TX_PIN for the UART TX, 26 is the default
* RS485_BAUD_RATE for the UART baud rate, 115200 is the default
* RS485_DIR_CONTROL for the GPIO that will handle TX/RX mode for the RS485 interface, 27 is the default
* RS485_delimiter used for input parsing, a single space " " is the default, can be set to any valid char
* Recommend disabling any watchdog in the ESP32 for basic use

## Documentation
* RS485_init()    Function to initialize the UART module
* RS485_send()    Function to send data over the UART lines
* RS485_rx_task() Function that handles reading the UART RX buffer and handles the data parsing
