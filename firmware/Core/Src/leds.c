#include "leds.h"
#include "dma.h"
#include <stdbool.h>

#define LEDS_NB 11

static uint8_t led_data[LEDS_NB][3] = {0};
static bool leds_busy = false;

void leds_init()
{
    //
}

void leds_hello()
{
    HAL_Delay(500);
    int idx = 0;
    static const int delay = 30;
    for (int i=0; i<8; i++) {
        leds_erase();
        leds_setColor(idx, 0, 0, 10);
        idx = (idx + 1) % 8;
        leds_apply();
        HAL_Delay(delay);
    }
    for (int i=0; i<8; i++) {
        leds_erase();
        leds_setColor(idx, 0, 10, 0);
        idx = (idx + 1) % 8;
        leds_apply();
        HAL_Delay(delay);
    }
    for (int i=0; i<8; i++) {
        leds_erase();
        leds_setColor(idx, 10, 0, 0);
        idx = (idx + 1) % 8;
        leds_apply();
        HAL_Delay(delay);
    }
    leds_erase();
    leds_setColor(8, 0, 0, 1);
    leds_apply();
}

void leds_setColor(int led_id, uint8_t red, uint8_t green, uint8_t blue)
{
    if (led_id >= LEDS_NB) return;

    led_data[led_id][0] = red;
    led_data[led_id][1] = green;
    led_data[led_id][2] = blue;
}

HAL_StatusTypeDef leds_apply()
{
    uint16_t pwmData[(24*LEDS_NB)+60];

    int i, j;
    for (i=0; i<LEDS_NB; i++) {
        for (j=0; j<8; j++) {
            pwmData[24 * i + j + 8]  = (led_data[i][0] & (1 << (7-j))) ? 33 : 16;   // RED
            pwmData[24 * i + j]      = (led_data[i][1] & (1 << (7-j))) ? 33 : 16;   // GREEN
            pwmData[24 * i + j + 16] = (led_data[i][2] & (1 << (7-j))) ? 33 : 16;   // BLUE
        }
    }

    for (i=24*LEDS_NB; i<(24*LEDS_NB)+60; i++) {
        pwmData[i] = 0;
    }
    
    while (leds_busy){};
    HAL_StatusTypeDef ret =  HAL_TIMEx_PWMN_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t *)pwmData, (24*LEDS_NB)+60);
    
    if (ret == HAL_OK) leds_busy = true;

    return ret;
}

void leds_erase()
{
    int i,j;
    for (i=0; i<LEDS_NB; i++) {
        for (j=0; j<3; j++) {
            led_data[i][j] = 0;
        }
    }
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIMEx_PWMN_Stop_DMA(htim, TIM_CHANNEL_3);

    leds_busy = false;
}