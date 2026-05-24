# TMP3X Interface driver for ESP32
This is a lightweight, modular C driver for interfacing ESP32-based microcontrollers to the TMP3x series of PCB mounted temperature sensors.

## Features 
*   Bare metal ADC and command processing ( no dependency on Arduino layer)
*   Modular header/source structure for easy inclusion

## Folder Structure
/components/rs485
├── tmp3x.h        # Public API for external use
├── tmp3x.c        # Core implementation
├── LICENSE.md     # License information
└── README.md      # This file

## Dependencies
* ESP32 SDK (ESD-IDF, Arduino or VSCode)
* ADC UNIT 1 with CHANNEL 4. DO not use with other ADC Units as it does cause conflicts with other systems
* FreeRTOS 

## Configuration
* Place the pwmfan folder inside of the project components folder
* In the main application C file, include the tmp3x.h file
* Recommend disabling any watchdog in the ESP32 for basic use

## Documentation
* tmp3x_init()    Function to initialize the temperature sensing
* float TEMPERATURE   Variable to hold calibrated and converted value to °C, is an external variable and can be accessed using the header file.
