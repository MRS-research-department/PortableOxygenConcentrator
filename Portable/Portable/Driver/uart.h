#ifndef UART_H
#define UART_H

#include "gd32f30x_gpio.h"
#include "Systick.h"
#include "stdio.h"

void uart_init(void);
int fputc(int ch, FILE *f);
void uart_data_transmit(uint8_t arr[], uint32_t length);

#endif
