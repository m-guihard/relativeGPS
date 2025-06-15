#ifndef __LORA_H__
#define __LORA_H__

#include <stdbool.h>

typedef enum {
    LORA_MSG_NONE,
    LORA_MSG_OK,
    LORA_MSG_READY,
    LORA_MSG_RESET,
    LORA_MSG_POSITION,
    LORA_MSG_INVALID,
    LORA_MSG_ERROR
} rylr_msg_t;

bool rylr_init(uint8_t address);
rylr_msg_t rylr_process_msg();
void rylr_usart_cb_process_data(const void* data, size_t len);
bool rylr_reset();

#endif