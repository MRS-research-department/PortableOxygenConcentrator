#ifndef DRIVALVE_H
#define DRIVALVE_H

#include "gd32f30x_gpio.h"
#include "Systick.h"

////��ŷ�����ʱ��
//unsigned char bit_EMC;
//unsigned int TEMC_Change = 40;  //�����л�ʱ�� 32*100ms = 3.2s
//unsigned int TEMC_COM    = 4 ;  //��ͬ��ʱ��, 2*100ms  = 200ms
//unsigned int Tswitch;
//unsigned int Tswitch_time; //��ŷ��л�ʱ��
//unsigned int T2timex;
//unsigned char EMC_step;


#define Valve1(x)        ((x) ? (gpio_bit_set(GPIOB,GPIO_PIN_2))  : (gpio_bit_reset(GPIOB,GPIO_PIN_2)))
#define Valve2(x)        ((x) ? (gpio_bit_set(GPIOB,GPIO_PIN_1))  : (gpio_bit_reset(GPIOB,GPIO_PIN_1)))

void 	RCU_Config(void);
void 	GPIO_config(void);
void 	Timer1_Init(void);
void 	Valve_Init(void);


#endif

