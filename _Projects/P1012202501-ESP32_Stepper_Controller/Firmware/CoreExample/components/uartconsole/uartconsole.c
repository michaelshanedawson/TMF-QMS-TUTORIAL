/*
* UART Console for ESP32 source file
* uartconsole.c
* Michael Dawson
* michaelshanedawson@gmail.com
*
* v0.0.1
*/

#include "uartconsole.h"
#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*Add includes for any drivers that need to be used with the UART console here*/
#include "../pwmfan/pwmfan.h"
#include "../nvssystem/nvssystem.h"
#include "../systemstatus/systemstatus.h"

/*Variables*/
char uartconsole_buffer[256]; // Buffer for UART console input
uint8_t uartconsole_buffer_index = 0; // Index for the buffer
char uartconsole_command[64]; // Buffer for commands
char uartconsole_argument[192]; // Buffer for command arguments

/*Define prototypes*/
void uartconsole_init(uint8_t UART_RX_PIN, uint8_t UART_TX_PIN, uint32_t BAUD_RATE, char* delimiter);
void uartconsole_send(const char* data);
void uartconsole_rx_task(void* pvParameters);
void uartconsole_parse_input(const char* input);
void uartconsole_process_command(const char* command, const char* argument);

/* This is where we will add any custom code to process terminal commands and provide any feedback*/
void uartconsole_process_command(const char* command, const char* argument)
{
    /*PROCESS COMMANDS AND ARGUMENTS*/
    /*Add additional commands below. Add additional header files above for any custom modules*/
    if ((strcmp(command, "help") == 0) || (strcmp(command, "?") == 0))
    {
        uartconsole_send("\n");
        uartconsole_send("Available commands:\n");
        uartconsole_send("help or ? - Show this help message\n");
        uartconsole_send("clear - Clear the console\n");
        uartconsole_send("---SYSTEM SETTINGS---\n");
        uartconsole_send("usefan # to set if the fan is installed, 0 or 1\n");
        uartconsole_send("\n");
    }

    /*System Settings*/
    else if (strcmp(command, "usefan") == 0)
    {       
        int fanVal = atoi(argument);
        IS_FAN_INSTALLED = fanVal;
        nvs_fan_write();
        char response[256];
        snprintf(response, sizeof(response), "Fan Installed Set to: %u\n", fanVal);
        uartconsole_send(response);         
    }
    else if (strcmp(command, "clear") == 0)
    {
        uartconsole_send("\033[H\033[J"); // Clear the console
    }
    else
    {
        uartconsole_send("Unknown command. Type 'help' for available commands.\n");
    }
}

void uartconsole_parse_input(const char* input)
{
    // Process the input received from UART
    // This function can be expanded to handle commands, arguments, etc.
    printf("Input received: %s\n", input);
    // For example, you could parse commands and execute corresponding functions
    char *token;
    token = strtok((char*)input, delimiter);
    if (token != NULL) {
        strncpy(uartconsole_command, token, sizeof(uartconsole_command) - 1);
        uartconsole_command[sizeof(uartconsole_command) - 1] = '\0'; // Ensure null termination
        printf("Command: %s\n", uartconsole_command);

        token = strtok(NULL, delimiter);
        if (token != NULL) {
            strncpy(uartconsole_argument, token, sizeof(uartconsole_argument) - 1);
            uartconsole_argument[sizeof(uartconsole_argument) - 1] = '\0'; // Ensure null termination
            printf("Argument: %s\n", uartconsole_argument);
        } else {
            uartconsole_argument[0] = '\0'; // No argument provided
        }
    }
    else {
        uartconsole_command[0] = '\0'; // No command provided
        uartconsole_argument[0] = '\0'; // No argument provided
    }
    // Process the command and argument
    uartconsole_process_command(uartconsole_command, uartconsole_argument);
}

void uartconsole_init(uint8_t UART_RX_PIN, uint8_t UART_TX_PIN, uint32_t BAUD_RATE, char* delimiter)
{
    const uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM_1, 1024 * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    uartconsole_buffer[uartconsole_buffer_index] = '\0'; // Null-terminate the buffer
    memset(uartconsole_buffer, 0, sizeof(uartconsole_buffer)); // Clear the buffer

    xTaskCreate(uartconsole_rx_task, "uart_rx_task", 1024 * 2, NULL, 2, NULL);
}

void uartconsole_send(const char* data)
{
    const int len = strlen(data);
    // Send data over UART
    uart_write_bytes(UART_NUM_1, data, len);
}

void uartconsole_rx_task(void* pvParameters)
{
    char* buffer = (char*)malloc(256);
    while (1) {
        int len = uart_read_bytes(UART_NUM_1, (uint8_t*)buffer, 256, 20 / portTICK_PERIOD_MS);
        if (len > 0) {
            buffer[len] = '\0'; // Null-terminate the string
            //printf("Received: %s\n", buffer);
            // Process the received data here
            if(buffer [strlen(buffer) -1]== '\r')
            {
                uartconsole_parse_input(uartconsole_buffer); // Parse the input
                uartconsole_buffer[256] = '\0'; // Null-terminate the buffer
                memset(uartconsole_buffer, 0, sizeof(uartconsole_buffer)); // Clear the buffer
            }

            else
            {
                strcat(uartconsole_buffer, buffer);
                //printf("Received: %s\n", uartconsole_buffer);                
            }
            
        }
    }
}
