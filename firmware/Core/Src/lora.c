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
#define MSG_LEN_OK 		5
#define MSG_LEN_READY	8
#define MSG_LEN_RESET	8
#define MSG_LEN_ERR		5
#define MSG_LEN_RCV		5

uint8_t find_next_crlf(uint8_t* buffer, uint8_t max);
void process_pos_msg(uint8_t* buffer);

static bool lora_test();
static bool lora_wait_for_answer(lora_msg_t answer, uint32_t timeout);
static bool lora_config_band();
static bool lora_config_rf_parameters();
static bool lora_config_address(uint8_t address);
static bool lora_config_networkid(uint8_t network_id);
static bool lora_config_cpin(const char* password);
static bool lora_config_crfop();

bool lora_init(uint8_t address)
{
    const uint8_t tries = 3;
    const char pwd[] = "A53FB94C";

    bool success = true;

    for (int i=0; i<tries; i++) {
        // success &= lora_wait_ready();
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

void lora_usart_cb_process_data(const void* data, size_t len) {

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

    if (msg_buffer_idx > 1 &&
        msg_buffer[msg_buffer_idx-2] == '\r' &&
        msg_buffer[msg_buffer_idx-1] == '\n') {

        new_rx_data = true;
    }
}

lora_msg_t lora_process_msg() {
    if (!new_rx_data) return LORA_MSG_NONE;

    lora_msg_t ret = LORA_MSG_NONE;
    uint8_t len = 0;

    if (strncmp((char*)msg_buffer, "+OK\r\n", MSG_LEN_OK) == 0) {
        ret = LORA_MSG_OK;
        len = 5;

    } else if (strncmp((char*)msg_buffer, "+READY\r\n", MSG_LEN_READY) == 0) {
        ret = LORA_MSG_READY;
        len = 8;

    } else if (strncmp((char*)msg_buffer, "+RESET\r\n", MSG_LEN_RESET) == 0) {
        ret = LORA_MSG_RESET;
        len = 8;

    } else if (strncmp((char*)msg_buffer, "+ERR=", MSG_LEN_ERR) == 0) {
        len = find_next_crlf(msg_buffer, MAX_MSG_LENGTH);
        if (len) {
            ret = LORA_MSG_ERROR;
            printer(USART_DEBUG, "[ERROR] LoRa error:\r\n", 21);
            printer(USART_DEBUG, (char*)msg_buffer, len);
        }

    } else if (strncmp((char*)msg_buffer, "+RCV=", MSG_LEN_RCV) == 0) {
        len = find_next_crlf(msg_buffer, MAX_MSG_LENGTH);
        if (len == 999) {
            ret = LORA_MSG_POSITION;
            process_pos_msg(&msg_buffer[MSG_LEN_RCV]);
        } else {
            ret = LORA_MSG_INVALID;
        }
    }

    if (len) {
        memmove(msg_buffer, &msg_buffer[len], MAX_MSG_LENGTH - len);
        memset(&msg_buffer[MAX_MSG_LENGTH - len], 0, len);
        msg_buffer_idx -= len;
    }

    new_rx_data = false;
    return ret;
}

uint8_t find_next_crlf(uint8_t* buffer, uint8_t max)
{
	uint8_t id_found = 0;

	for (int i=1; i<max; i++) {
		if (buffer[i-1] == '\r' && buffer[i] == '\n') {
			id_found = i;
			break;
		}
	}

	return id_found;
}

void process_pos_msg(uint8_t* buffer)
{
    // sscanf(buffer, "");
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
    char buffer[14] = "AT+ADDRESS=0\r\n";
    buffer[11] += address;
    printer(USART_LORA, buffer, 14);

    return lora_wait_for_answer(LORA_MSG_OK, 1000);
}

bool lora_config_networkid(uint8_t network_id)
{
    char buffer[17] = "AT+NETWORKID=00\r\n";
    buffer[13] += network_id / 10;
    buffer[14] += network_id % 10;
    printer(USART_LORA, buffer, 17);

    return lora_wait_for_answer(LORA_MSG_OK, 1000);
}

bool lora_config_cpin(const char* password)
{
    char buffer[18] = "AT+CPIN=00000000\r\n";
    for (int i=0; i<8; i++) {
        buffer[8 + i] = password[i];
    }
    printer(USART_LORA, buffer, 18);

    return lora_wait_for_answer(LORA_MSG_OK, 2000);
}

bool lora_config_crfop()
{
    // TOD: determine the output power
    printer(USART_LORA, "AT+CRFOP=11\r\n", 13);

    return lora_wait_for_answer(LORA_MSG_OK, 2000);
}