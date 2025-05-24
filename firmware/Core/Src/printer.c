#include "printer.h"

void printer(USART_TypeDef * USART_LINE, char* data, int length)
{
    uint8_t* d = data;

    for (; length > 0; --length, ++d) {
        LL_USART_TransmitData8(USART_LINE, *d);
        while (!LL_USART_IsActiveFlag_TXE(USART_LINE)) {}
    }

    while (!LL_USART_IsActiveFlag_TC(USART_LINE)) {}
}