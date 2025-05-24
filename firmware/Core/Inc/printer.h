#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "usart.h"

void printer(USART_TypeDef * USART_LINE, char* data, int length);

#endif