#ifndef __LEDS_H__
#define __LEDS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tim.h"

void leds_init();
void leds_hello();
void leds_setColor(int led_id, uint8_t red, uint8_t green, uint8_t blue);
HAL_StatusTypeDef leds_apply();
void leds_erase();

#ifdef __cplusplus
}
#endif

#endif /* __LEDS_H__ */