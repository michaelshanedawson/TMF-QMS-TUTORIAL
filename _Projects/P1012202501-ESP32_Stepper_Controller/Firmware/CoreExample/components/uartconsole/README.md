# PWM fan driver for ESP32
This is a lightweight, modular C driver for interfacing ESP32-based microcontrollers with most 4 pin PWM controlled fans.

## Features 
*   Bare metal PWM and tachometer reading ( no dependency on Arduino layer)
*   Modular header/source structure for easy inclusion

## Folder Structure
/components/pwmfan
├── pwmfan.h        # Public API for external use
├── pwmfan.c        # Core implementation
├── LICENSE.md      # License information
└── README.md       # This file

## Dependencies
* ESP32 SDK (ESD-IDF, Arduino or VSCode)
* LEDC + PULSECNT ESP32 modules
* FreeRTOS 

## Configuration
* Place the pwmfan folder inside of the project components folder
* In the main application C file, include the pwmfan.h file
* FAN_PWM_PIN for the desired PWM output pin, 17 is the default
* FAN_TACH_PIN for the desired tachometer input pin, 33 is the default
* FAN_PULSE_PER_REV the number of pulses the fan generates per revolution, typically it is 2
* Recommend disabling any watchdog in the ESP32 for basic use

## Documentation
* fan_init()    Function to initialize the PWM system and set an initial fan speed
* fan_set()     Function to set a new speed value to the fan via PWM
* get_fan_rpm() Function to get the current RPM of the fan as read by the tach pin
