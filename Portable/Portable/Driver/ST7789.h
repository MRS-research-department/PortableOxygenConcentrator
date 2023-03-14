#ifndef ST7789_H
#define ST7789_H

#include "gd32f30x_gpio.h"
#include "Systick.h"
#include "LCD.h"

void LCD_Init(void);
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)	;


#endif
