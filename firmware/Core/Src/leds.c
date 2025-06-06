#include "leds.h"
#include "dma.h"
#include <stdbool.h>
#include "tim.h"
#include "printer.h"

#define LEDS_NB 11

static uint8_t led_data[LEDS_NB][3] = {0};
volatile static bool leds_busy = false;

uint16_t leds_buffer_dma[(24*LEDS_NB)+60] = {0};

void leds_init()
{
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_7, (uint32_t)&TIM1->DMAR);
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_7, (uint32_t)leds_buffer_dma);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, sizeof(leds_buffer_dma) / sizeof((leds_buffer_dma)[0]));
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_7);

    LL_TIM_ConfigDMABurst(TIM1, LL_TIM_DMABURST_BASEADDR_CCR3, LL_TIM_DMABURST_LENGTH_1TRANSFER);
    LL_TIM_EnableDMAReq_CC3(TIM1);
    LL_TIM_EnableCounter(TIM1);
    LL_TIM_EnableAllOutputs(TIM1);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH3N);
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
    leds_setColor(8, 1, 0, 0);
    leds_apply();
}

void leds_setColor(int led_id, uint8_t red, uint8_t green, uint8_t blue)
{
    if (led_id >= LEDS_NB || led_id < 0) return;

    led_data[led_id][0] = red;
    led_data[led_id][1] = green;
    led_data[led_id][2] = blue;
}

void leds_apply()
{
    int i, j;
    for (i=0; i<LEDS_NB; i++) {
        for (j=0; j<8; j++) {
            leds_buffer_dma[24 * i + j + 8]  = (led_data[i][0] & (1 << (7-j))) ? 33 : 16;   // RED
            leds_buffer_dma[24 * i + j]      = (led_data[i][1] & (1 << (7-j))) ? 33 : 16;   // GREEN
            leds_buffer_dma[24 * i + j + 16] = (led_data[i][2] & (1 << (7-j))) ? 33 : 16;   // BLUE
        }
    }

    for (i=24*LEDS_NB; i<(24*LEDS_NB)+60; i++) {
        leds_buffer_dma[i] = 0;
    }

    while (LL_DMA_IsActiveFlag_TC7(DMA1)) {
        printer(USART_DEBUG, "LED update too fast\r\n", 21);
        HAL_Delay(50);
    }
    
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_7);
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