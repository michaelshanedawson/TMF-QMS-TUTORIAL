/*
* RS-485 interface for ESP32 source file
* RS485.c
* Michael Dawson
* michaelshanedawson@gmail.com
*
* v0.0.1
*/

#include "RS485.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//Add includes for any drivers that need to be used with the RS485 console here
#include "../pwmfan/pwmfan.h"
#include "../drv8825/drv8825.h"
#include "../nvssystem/nvssystem.h"
#include "../systemstatus/systemstatus.h"
#include "../tmp3x/tmp3x.h"

// Variables
char RS485_buffer[256]; // Buffer for UART console input
uint8_t RS485_buffer_index = 0; // Index for the buffer
char RS485_command[64]; // Buffer for commands
char RS485_argument[192]; // Buffer for command arguments

/*Define prototypes*/
void RS485_init(uint8_t RS485_RX_PIN, uint8_t RS485_TX_PIN, uint32_t RS485_BAUD_RATE, uint8_t RS485_DIR_CONTROL, char* RS485_delimiter);
void RS485_send(const char* data);
static void RS485_tx_task(char* arg);
static void RS485_rx_task(char* arg);
void RS485_parse_input(const char* input);
void RS485_process_command(const char* command, const char* argument);

/* This is where we will add any custom code to process terminal commands and provide any feedback*/
void RS485_process_command(const char* command, const char* argument)
{
    // Process the command and argument
    // This function can be expanded to handle different commands
    if (strcmp(command, "help") == 0)
    {
        RS485_send("\n");
        RS485_send("Available commands:\n");
        RS485_send("help - Show this help message\n");
        RS485_send("echo <message> - Echo the message back\n");
        RS485_send("clear - Clear the console\n");
        RS485_send("\n");
        RS485_send("---MOTOR COMMANDS---\n");
        RS485_send("motorspeed # to set speed, 0 to 100\n");
        RS485_send("\n");
        RS485_send("---STATUS COMMANDS---\n");
        RS485_send("getcount - This will get current cycle count\n");
        RS485_send("clearcount - This will reset the cycle count to 0\n");
        RS485_send("writecount - This will write the current cycle count to 0\n");
        RS485_send("getstatus - This will get current satatus byte\n");
        RS485_send("setstatus # to change the status byte\n");
        RS485_send("\n");
        RS485_send("---TEMPERATURE SENSOR---\n");
        RS485_send("gettemp - This will get the current average temperature of the PCB by the DRV8825\n");
        RS485_send("\n");
        // Add more commands as needed
    }

     else if (strcmp(command, "gettemp") == 0)
    {
        char response[256];
        snprintf(response, sizeof(response), "Current system temperature in C is: %f\n", TEMPERATURE);
        RS485_send(response);
    }

    else if (strcmp(command, "getstatus") == 0)
    {
        char response[256];
        snprintf(response, sizeof(response), "Current system status is: %u\n", STATUS_BYTE);
        RS485_send(response);
    }

    else if (strcmp(command, "setstatus") == 0)
    {       
        int statusVal = atoi(argument);
        STATUS_BYTE = statusVal;        
        char response[256];
        snprintf(response, sizeof(response), "Status Byte set to: %u\n", statusVal);
        RS485_send(response);         
    }

    else if (strcmp(command, "getcount") == 0)
    {
        char response[256];
        snprintf(response, sizeof(response), "Current cycle count is: %lu\n", CYCLE_COUNT);
        RS485_send(response);
    }

    else if (strcmp(command, "clearcount") == 0)
    {        
        RS485_send("Resetting stored cycle count to 0\n");
        nvs_clear();
        nvs_read();
    }

    else if (strcmp(command, "writecount") == 0)
    {        
        RS485_send("Writing current cycle count to NVS.\n");
        nvs_write();
    }

    else if (strcmp(command, "motorspeed") == 0)
    {
        // Extract stepper motor speed value from the argument
        int motor_speed = atoi(argument);
        if (motor_speed < 0 || motor_speed > 100)
        {
            RS485_send("Error: Stepper motor speed must be between 0 and 10.\n");
        }
        else
        {
            DRV8825_SPEED(motor_speed);
            char response[256];
            snprintf(response, sizeof(response), "Stepper Motor speed set to: %d%%\n", motor_speed);
            RS485_send(response);
        }
    }

    else if (strcmp(command, "echo") == 0)
    {
        char response[256];
        snprintf(response, sizeof(response), "Echo: %s\n", argument);
        RS485_send(response);
    }    
    else if (strcmp(command, "clear") == 0)
    {
        RS485_send("\033[H\033[J"); // Clear the console
    }
    else if (strcmp(command, "exit") == 0)
    {
        RS485_send("Exiting console.\n");
        // Add any cleanup code here if necessary
        vTaskDelete(NULL); // Delete the task if needed
    }
    else
    {
        RS485_send("Unknown command. Type 'help' for available commands.\n");
    }
}

void RS485_parse_input(const char* input)
{
    // Process the input received from UART
    // This function can be expanded to handle commands, arguments, etc.
    //printf("Input received: %s\n", input);
    // For example, you could parse commands and execute corresponding functions
    char *token;
    token = strtok((char*)input, RS485_delimiter);
    if (token != NULL) {
        strncpy(RS485_command, token, sizeof(RS485_command) - 1);
        RS485_command[sizeof(RS485_command) - 1] = '\0'; // Ensure null termination
        //printf("Command: %s\n", RS485_command);

        token = strtok(NULL, RS485_delimiter);
        if (token != NULL) {
            strncpy(RS485_argument, token, sizeof(RS485_argument) - 1);
            RS485_argument[sizeof(RS485_argument) - 1] = '\0'; // Ensure null termination
            //printf("Argument: %s\n", RS485_argument);
        } else {
            RS485_argument[0] = '\0'; // No argument provided
        }
    }
    else {
        RS485_command[0] = '\0'; // No command provided
        RS485_argument[0] = '\0'; // No argument provided
    }
    // Process the command and argument
    RS485_process_command(RS485_command, RS485_argument);
}

void RS485_init(uint8_t RS485_RX_PIN, uint8_t RS485_TX_PIN, uint32_t RS485_BAUD_RATE, uint8_t RS485_RS485_DIR_CONTROL, char* RS485_delimiter)
{
    const uart_config_t uart_config = {
        .baud_rate = RS485_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    //Configure direction control GPIO
    gpio_reset_pin(RS485_RS485_DIR_CONTROL);
    gpio_set_direction(RS485_RS485_DIR_CONTROL, GPIO_MODE_OUTPUT);
    gpio_set_level(RS485_RS485_DIR_CONTROL, 0);

    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM_0, 1024 * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);
    uart_set_pin(UART_NUM_0, RS485_TX_PIN, RS485_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    RS485_buffer[RS485_buffer_index] = '\0'; // Null-terminate the buffer
    memset(RS485_buffer, 0, sizeof(RS485_buffer)); // Clear the buffer

    xTaskCreate(RS485_rx_task, "rs485_rx_task", 1024 * 2, NULL, 2, NULL);
}

void RS485_send(const char* data)
{
    const int len = strlen(data);
    //Set RS485_DIR_CONTROL pin to proper level
    gpio_set_level(RS485_DIR_CONTROL, 1);
    vTaskDelay(10 / portTICK_PERIOD_MS);

    // Send data over UART
    uart_write_bytes(UART_NUM_0, data, len);

    //Reset RS485_DIR_CONTROL back to listen state
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(RS485_DIR_CONTROL, 0);
}

static void RS485_tx_task(char* arg)
{
    char* data = arg;
    RS485_send(data);
    vTaskDelete(NULL);
}

static void RS485_rx_task(char* arg)
{
    char* buffer = (char*)malloc(256);
    while (1) {
        int len = uart_read_bytes(UART_NUM_0, (uint8_t*)buffer, 256, 20 / portTICK_PERIOD_MS);
        if (len > 0) {
            buffer[len] = '\0'; // Null-terminate the string
            //printf("Received: %s\n", buffer);
            // Process the received data here
            if(buffer [strlen(buffer) -1]== '\r')
            {
                RS485_parse_input(RS485_buffer); // Parse the input
                RS485_buffer[256] = '\0'; // Null-terminate the buffer
                memset(RS485_buffer, 0, sizeof(RS485_buffer)); // Clear the buffer
            }

            else
            {
                strcat(RS485_buffer, buffer);
                //printf("Received: %s\n", RS485_buffer);                
            }
            
        }
    }
}
