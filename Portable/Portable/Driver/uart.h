#ifndef UART_H
#define UART_H

#include "gd32f30x.h"
#include "Systick.h"
#include "stdio.h"

extern	unsigned char USART0RX_Buffer[15];
extern unsigned int  O2_concent;

extern void UART0_SendByte(unsigned char tdata);
extern void UART0_PutString(char *str);

extern void UART0_Send_O2CMD(void);
extern void UART0_O2_para(void);

void uart_init_config(void);
int fputc(int ch, FILE *f);
void USART0_IRQHandler(void);
void UART0_SendByte(unsigned char tdata);
void UART_O2_Pare(void);

#endif
