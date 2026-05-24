# NVS Interface Driver for ESP32
This is a lightweight, modular C driver for interfacing with the non-volatile storage in ESP32-based microcontrollers.

## Features 
*   Bare metal NVS interfacing ( no dependency on Arduino layer)
*   Modular header/source structure for easy inclusion

## Folder Structure
/components/nvssystem
├── nvssystem.h        # Public API for external use
├── nvssystem.c        # Core implementation
├── LICENSE.md      # License information
└── README.md       # This file

## Dependencies
* ESP32 SDK (ESD-IDF, Arduino or VSCode)
* ESP32 Non-Volatile storage
* FreeRTOS 

## Configuration
* Place the pwmfan folder inside of the project components folder
* In the main application C file, include the nvssystem.h file
* Recommend disabling any watchdog in the ESP32 for basic use
* In the nvssystem.c file, add any headers to modules that need to interface with the NVS system

## Documentation
* nvs_init()    Function to initialize the Non-Volatile memory system
