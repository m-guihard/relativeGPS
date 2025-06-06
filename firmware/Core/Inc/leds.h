#ifndef __LEDS_H__
#define __LEDS_H__

#include "tim.h"

void leds_init();
void leds_hello();
void leds_setColor(int led_id, uint8_t red, uint8_t green, uint8_t blue);
void leds_apply();
void leds_erase();

#endif /* __LEDS_H__ */