#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "usart.h"
#include "lora.h"
#include "printer.h"

#define MAX_MSG_LENGTH 50
static uint8_t rxByte[2];
static uint8_t buffer_idx = 0;
static uint8_t buffer_line[MAX_MSG_LENGTH+1];
static uint8_t msg_rx[MAX_MSG_LENGTH];

void lora_init()
{
    HAL_UART_Receive_IT(&huart1, rxByte, 1);
}

void lora_process_msg()
{
    printer(buffer_line, sizeof(buffer_line));

    if (strncmp(msg_rx, "RGM", 3) == 0 && msg_rx[23] == '#') {
        // Position msg from another module

        int matches = 0;
        int latitude = 0;
        int longitude = 0;
        int user_id;
        uint8_t latitude_letter = msg_rx[11];
        uint8_t longitude_letter = msg_rx[20];

        if (latitude_letter == 'N') {
            if (longitude_letter == 'E') {
                matches = sscanf(&msg_rx[3], "%dN%dE%d#", &latitude, &longitude, &user_id);
            } else if (longitude_letter == 'W') {
                matches = sscanf(&msg_rx[3], "%dN%dW%d#", &latitude, &longitude, &user_id);
            }
        } else if (latitude_letter == 'S') {
            if (longitude_letter == 'E') {
                matches = sscanf(&msg_rx[3], "%dS%dE%d#", &latitude, &longitude, &user_id);
            } else if (longitude_letter == 'W') {
                matches = sscanf(&msg_rx[3], "%dS%dW%d#", &latitude, &longitude, &user_id);
            }
        }

        if (matches == 3) {
            #ifdef DEBUG
            {
                // Debug print
                uint8_t debug_text[60];
                sprintf(debug_text, "LoRa position decoded: %d°%s%d°%s | %d", latitude, latitude_letter, longitude, longitude_letter, user_id);
                printer(debug_text, sizeof(debug_text));
            } 
            #endif
        }

    }

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (buffer_idx < MAX_MSG_LENGTH) {
        memcpy(buffer_line+buffer_idx, rxByte, 1);
        buffer_idx++;
    }

	HAL_UART_Receive_IT(&huart1, rxByte, 1);
}
