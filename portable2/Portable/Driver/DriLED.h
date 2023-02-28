#ifndef DRILED_H
#define DRILED_H

#include "gd32f30x.h"
#include "systick.h"

#define		LED_PIN		GPIO_PIN_1
#define		LED_PORT	GPIOC

//宏定义控制LED，1为高电平，0为低电平
#define LED(n)	(n?gpio_bit_set(GPIOC,GPIO_PIN_1):gpio_bit_reset(GPIOC,GPIO_PIN_1))

void Dri_LED_Gpio_Init();

#endif


