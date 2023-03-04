#ifndef KEY_H
#define KEY_H

#include "gd32f30x_gpio.h"

void Key_GPIO_Init(void);

FlagStatus Key1(void);
FlagStatus Key2(void);
FlagStatus Key3(void);
FlagStatus Key4(void);
#endif

