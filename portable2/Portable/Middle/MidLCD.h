#ifndef MIDLCD_H
#define MIDLCD_H

#include "gd32f30x_gpio.h"
#include "Systick.h"
#include "DriLCD.h"
#include "DriFont.h"

void Mid_LCD_Init(void);
void Mid_LCD_Clear(uint16_t color);
void Mid_LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode);
void Mid_LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *p, uint8_t size, uint8_t mode);
void Mid_Disp_Concentration(unsigned int x,unsigned int y,unsigned int temp);
void Mid_Window(void);
#endif
