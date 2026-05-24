# DRV8825 Stepper Controller Driver for ESP32
This is a lightweight, modular C driver for interfacing ESP32-based microcontrollers with the DRV8825 Stepper Motor Driver IC.

## Features 
*   Bare metal interfacing ( no dependency on Arduino layer)
*   Modular header/source structure for easy inclusion

## Folder Structure
/components/nvssystem
├── drv8825.h        # Public API for external use
├── drv8825.c        # Core implementation
├── LICENSE.md      # License information
└── README.md       # This file

## Dependencies
* ESP32 SDK (ESD-IDF, Arduino or VSCode)
* ESP32 LEDC Driver
* FreeRTOS 

## Configuration
* Place the drv8825 folder inside of the project components folder
* In the main application C file, include the drv8825.h file
* Recommend disabling any watchdog in the ESP32 for basic use

## Documentation
* DRV8825_INIT()    Function to initialize the DRV8825 module
