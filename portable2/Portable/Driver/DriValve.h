#ifndef DRIVALVE_H
#define DRIVALVE_H

#include "gd32f30x_gpio.h"
#include "Systick.h"

////电磁阀工作时间
//unsigned char bit_EMC;
//unsigned int TEMC_Change = 40;  //设置切换时间 32*100ms = 3.2s
//unsigned int TEMC_COM    = 4 ;  //共同打开时间, 2*100ms  = 200ms
//unsigned int Tswitch;
//unsigned int Tswitch_time; //电磁阀切换时间
//unsigned int T2timex;
//unsigned char EMC_step;


#define Valve1(x)        ((x) ? (gpio_bit_set(GPIOB,GPIO_PIN_2))  : (gpio_bit_reset(GPIOB,GPIO_PIN_2)))
#define Valve2(x)        ((x) ? (gpio_bit_set(GPIOB,GPIO_PIN_1))  : (gpio_bit_reset(GPIOB,GPIO_PIN_1)))

void 	RCU_Config(void);
void 	GPIO_config(void);
void 	Timer1_Init(void);
void 	Valve_Init(void);


#endif

