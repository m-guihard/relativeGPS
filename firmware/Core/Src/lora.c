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

#define POSITION_MSG_LENGTH 25

static bool lora_test();
static bool lora_wait_for_answer(lora_msg_t answer, uint32_t timeout);
static bool lora_config_band();
static bool lora_config_rf_parameters();
static bool lora_config_address(uint8_t address);
static bool lora_config_networkid(uint8_t network_id);
static bool lora_config_cpin(uint8_t* password);
static bool lora_config_crfop();

bool lora_init(uint8_t address)
{
    const uint8_t* pwd = "A53FB94C";
    for (int i=0; i< 3; i++) {
        bool success = true;
        success &= lora_test();
        success &= lora_config_band();
        success &= lora_config_rf_parameters();
        success &= lora_config_address(address);
        success &= lora_config_networkid(12);
        success &= lora_config_cpin(pwd);
        success &= lora_config_crfop();
        
        if (success) {
            return true;
        }
    }

    return false;
}

void lora_usart_process_data(const void* data, size_t len) {
    printer(USART_DEBUG, data, len);
    // Add bytes to local buffer
    if (msg_buffer_idx < MAX_MSG_LENGTH - len) {
        memcpy(&msg_buffer[msg_buffer_idx], data, len);
        msg_buffer_idx += len;
    } else {
        // Overflow: a too long message was received. Replace it with the current message.
        memset(msg_buffer, 0, MAX_MSG_LENGTH);
        memcpy(msg_buffer, data, len);
        msg_buffer_idx = len;
    }
    new_rx_data = true;
}

lora_msg_t lora_process_msg() {
    if (!new_rx_data) return LORA_MSG_NONE;

    lora_msg_t ret = LORA_MSG_NONE;
    uint8_t len = 0;

    if (!memcmp(msg_buffer, "+OK", 3)) {
        ret = LORA_MSG_OK;
        len = 5;

    } else if (!memcmp(msg_buffer, "+RESET", 6)) {
        ret = LORA_MSG_RESET;
        len = 5;

    } else if (!memcmp(msg_buffer, "+RCV", 4)) {
        if (msg_buffer_idx < POSITION_MSG_LENGTH) {
            ret = LORA_MSG_NONE;
        } else {
            // TODO: Process the position msg

            ret = LORA_MSG_POSITION;
            len = POSITION_MSG_LENGTH + 2;
        }
    }

    if (len) {
        memmove(msg_buffer, &msg_buffer[len], MAX_MSG_LENGTH - len);
        msg_buffer_idx -= len;
    }
    

    new_rx_data = false;
    return ret;
}

bool lora_wait_for_answer(lora_msg_t answer, uint32_t timeout)
{
    const uint32_t start = HAL_GetTick();
    lora_msg_t msg = LORA_MSG_NONE;
    while (msg != answer && (HAL_GetTick() - start) < timeout) {
        msg = lora_process_msg();
    }

    return msg == answer;
}

bool lora_test()
{
    printer(USART_LORA, "AT\r\n", 4);

    return lora_wait_for_answer(LORA_MSG_OK, 1000);
}

bool lora_reset()
{
    printer(USART_LORA, "AT+RESET\r\n", 10);

    return lora_wait_for_answer(LORA_MSG_RESET, 1000);
}

bool lora_config_band()
{
    printer(USART_LORA, "AT+BAND=868000000,M\r\n", 21);

    return lora_wait_for_answer(LORA_MSG_OK, 1000);
}

bool lora_config_rf_parameters()
{
    // TODO: determine those parameters
    printer(USART_LORA, "AT+PARAMETER=9,7,1,12\r\n",23);

    return lora_wait_for_answer(LORA_MSG_OK, 1000);
}

bool lora_config_address(uint8_t address)
{
    uint8_t buffer[14] = "AT+ADDRESS=0\r\n";
    buffer[11] += address;
    printer(USART_LORA, buffer, 14);

    return lora_wait_for_answer(LORA_MSG_OK, 1000);
}

bool lora_config_networkid(uint8_t network_id)
{
    uint8_t buffer[17] = "AT+NETWORKID=00\r\n";
    buffer[13] += network_id / 10;
    buffer[14] += network_id % 10;
    printer(USART_LORA, buffer, 17);

    return lora_wait_for_answer(LORA_MSG_OK, 1000);
}

bool lora_config_cpin(uint8_t* password)
{
    uint8_t buffer[18] = "AT+CPIN=00000000\r\n";
    for (int i=0; i<8; i++) {
        buffer[8 + i] = password[i];
    }
    printer(USART_LORA, buffer, 18);

    return lora_wait_for_answer(LORA_MSG_OK, 1000);
}

bool lora_config_crfop()
{
    // TOD: determine the output power
    printer(USART_LORA, "AT+CRFOP=10\r\n", 13);

    return lora_wait_for_answer(LORA_MSG_OK, 1000);
}