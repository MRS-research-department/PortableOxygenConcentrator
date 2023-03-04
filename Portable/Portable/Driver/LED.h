#ifndef LED_H
#define LED_H

#include "gd32f30x_gpio.h"
#include "Systick.h"

#define LED(n)	(n?gpio_bit_set(GPIOC,GPIO_PIN_1):gpio_bit_reset(GPIOC,GPIO_PIN_1))

void LED_Init(void);

#endif
