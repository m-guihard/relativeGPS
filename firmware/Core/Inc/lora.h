#ifndef __LORA_H__
#define __LORA_H__

#include <stdbool.h>

typedef enum {
    LORA_MSG_NONE,
    LORA_MSG_OK,
    LORA_MSG_RESET,
    LORA_MSG_POSITION,
} lora_msg_t;

bool lora_init(uint8_t address);
lora_msg_t lora_process_msg();
void lora_usart_process_data(const void* data, size_t len);

#endif