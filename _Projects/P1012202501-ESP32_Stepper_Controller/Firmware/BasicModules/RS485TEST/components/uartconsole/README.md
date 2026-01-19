# UART Console Driver for ESP32
This is a lightweight, modular C driver for using the ESP32 UART interface over a standard RS-232 serial port or a USB to UART converter device.

## Features 
*   Bare metal UART console interface ( no dependency on Arduino layer)
*   Modular header/source structure for easy inclusion

## Folder Structure
/components/uartconsole
├── uartconsole.h        # Public API for external use
├── uartconsole.c        # Core implementation
├── LICENSE.md      # License information
└── README.md       # This file

## Dependencies
* ESP32 SDK (ESD-IDF, Arduino or VSCode)
* FreeRTOS 

## Configuration
* Place the uartconsole folder inside of the project components folder
* In the main application C file, include the `uartconsole.h` file
* In the main.c file add the following lines and adjust for your configuration
`uint8_t UART_RX_PIN = 19; // GPIO pin used for the UART RX`
`uint8_t UART_TX_PIN = 21; // GPIO pin used for the UART TX`
`uint32_t BAUD_RATE = 115200; // Baud rate for UART communication`
`char* delimiter = " "; // Delimiter for input parsing`
* In the main loop, call the following to configure, install and initiate the task for the UART console
`uartconsole_init(UART_RX_PIN, UART_TX_PIN, BAUD_RATE, delimiter);`
* If you want to use the UART console to interface with any custom drivers, in modify the uartconsole.c file and add the 
drivers header file under the line `//Add includes for any drivers that need to be used with the UART console here`
* Recommend disabling any watchdog in the ESP32 for basic use

## Documentation
* uartconsole_init()    Function to initialize the UART api
* uartconsole_send()     Function to send ASCII text from the URT interface
* uartconsole_rx_task() Initiates the FreeRTOS task to receive data to the ESP32
* uartconsole_parse_input() Function that parses the ASCII input and tokenizes the data into useable commands and arguments
* uartconsole_process_command() Function that takes the parsed tokens and acts upon them. Add your custom code here to perform specific actions.

## Building Notes
* Stick to ESP-IDF version 5.2.1 as version 6.0 seems to have updated the legacy drivers for newer APIs. Will need to recode in the future.
