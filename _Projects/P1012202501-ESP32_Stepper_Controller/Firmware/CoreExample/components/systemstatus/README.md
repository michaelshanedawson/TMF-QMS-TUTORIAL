# Status Monitoring driver for ESP32
This is a lightweight, modular C driver for interfacing ESP32-based microcontrollers to monitor systems and sensors.

## Features 
*   Bare metal command processing ( no dependency on Arduino layer)
*   Modular header/source structure for easy inclusion

## Folder Structure
/components/rs485
├── systemstatus.h        # Public API for external use
├── systemstatus.c        # Core implementation
├── LICENSE.md     # License information
└── README.md      # This file

## Dependencies
* ESP32 SDK (ESD-IDF, Arduino or VSCode)
* FreeRTOS 

## Configuration
* Place the pwmfan folder inside of the project components folder
* In the main application C file, include the systemstatus.h file
* In the main application fle, add this line : uint8_t STATUS_LED_PIN = 4; where the number is for the GPIO that has a status LED attached
* In the systemstatus.c file, add the header file of any sub module that you wish to monitor such as a sensor driver
* Recommend disabling any watchdog in the ESP32 for basic use

## Documentation
* status_init()             Basic initialization function for the monitoring module
* status_monitor_task()     The function that performs the monitoring