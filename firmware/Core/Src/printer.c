#include "printer.h"

void printer(uint8_t* data, int length)
{
    HAL_UART_Transmit(&huart2, data, length, 1000);
    uint8_t carriage_return[2] = "\n\r";
    HAL_UART_Transmit(&huart2, carriage_return, 2, 1000);
}