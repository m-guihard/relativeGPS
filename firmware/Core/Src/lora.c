#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "usart.h"
#include "lora.h"
#include "printer.h"

// UART RX handling
#define MAX_MSG_LENGTH 50
static size_t msg_buffer_idx = 0;
static uint8_t msg_buffer[MAX_MSG_LENGTH];
static bool new_rx_data = false;

// Messages that require an answer
static bool request_sent = false;
static bool ok_received = false;

void lora_init()
{
    
}

void lora_usart_process_data(const void* data, size_t len) {
    const uint8_t* d = data;

    // Add bytes to local buffer
    if (msg_buffer_idx < MAX_MSG_LENGTH - len) {
        memcpy(&msg_buffer[msg_buffer_idx], data, len);
        msg_buffer_idx += len;
        new_rx_data = true;
    } else {
        // Overflow: a too long message was received. Replace it with the current message.
        memset(msg_buffer, 0, MAX_MSG_LENGTH);
        memcpy(msg_buffer, data, len);
        msg_buffer_idx = len;
        new_rx_data = true;
    }
    
    // TODO: Set flag to process data in main thread
}

void lora_search_setup_answer(lora_msg_t msg_type)
{
    if (!new_rx_data) return;
    new_rx_data = false;

    if (msg_buffer[0] != "+") {
        memset(msg_buffer, 0, MAX_MSG_LENGTH);
        msg_buffer_idx = 0;
    }

    // switch (msg_type) {
    //     case OK: {
    //         if (msg_buffer_idx >= 3) {
    //             if () {

    //             } else {
    //                 return 0;
    //             }
    //         }
    //     }
    // }  

    // if (strncmp(msg_rx, "RGM", 3) == 0 && msg_rx[23] == '#') {
    //     // Position msg from another module

    //     int matches = 0;
    //     int latitude = 0;
    //     int longitude = 0;
    //     int user_id;
    //     uint8_t latitude_letter = msg_rx[11];
    //     uint8_t longitude_letter = msg_rx[20];

    //     if (latitude_letter == 'N') {
    //         if (longitude_letter == 'E') {
    //             matches = sscanf(&msg_rx[3], "%dN%dE%d#", &latitude, &longitude, &user_id);
    //         } else if (longitude_letter == 'W') {
    //             matches = sscanf(&msg_rx[3], "%dN%dW%d#", &latitude, &longitude, &user_id);
    //         }
    //     } else if (latitude_letter == 'S') {
    //         if (longitude_letter == 'E') {
    //             matches = sscanf(&msg_rx[3], "%dS%dE%d#", &latitude, &longitude, &user_id);
    //         } else if (longitude_letter == 'W') {
    //             matches = sscanf(&msg_rx[3], "%dS%dW%d#", &latitude, &longitude, &user_id);
    //         }
    //     }

    //     if (matches == 3) {
    //         #ifdef DEBUG
    //         {
    //             // Debug print
    //             uint8_t debug_text[60];
    //             sprintf(debug_text, "LoRa position decoded: %d°%s%d°%s | %d", latitude, latitude_letter, longitude, longitude_letter, user_id);
    //             printer(USART_DEBUG, debug_text, sizeof(debug_text));
    //         } 
    //         #endif
    //     }

    // }

}

