#ifndef MIDLCD_H
#define MIDLCD_H

#include "gd32f30x_gpio.h"
#include "Systick.h"
#include "DriLCD.h"
#include "DriFont.h"

void Mid_LCD_Init();
void Mid_LCD_Clear(uint16_t color);
void Mid_LCD_ShowChar(uint16_t x, uint16_t y, char chr, uint8_t size);
void Mid_LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p);

#endif
