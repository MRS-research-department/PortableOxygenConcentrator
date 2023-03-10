#ifndef UART_H
#define UART_H

#include "gd32f30x.h"
#include "Systick.h"
#include "stdio.h"

extern unsigned int  O2_concent;

extern unsigned char UART0_Rxcount;    //接收数据长度
extern unsigned char UART0_timeover;   //uart0超时时间
extern unsigned char UART0_RxSuccess;  //uart0接收成功


extern unsigned char USART0TX_Buffer[8];
extern unsigned char USART0RX_Buffer[15];

extern unsigned char O2_gear;
extern unsigned char O2_mode;
extern unsigned int  O2_concent;     //氧气浓度
extern unsigned char O2_number; 

void uart_config(void);
void UART0_Send_O2CMD(void);
void UART0_O2_para(void);
void USART0_IRQHandler(void);
void uart_data_transmit(uint8_t arr[], uint32_t length);

#endif
