#ifndef DIRLCD_H
#define DIRLCD_H

#include "gd32f30x_gpio.h"
#include "Systick.h"

extern uint16_t POINT_COLOR;		//画笔颜色定义
extern uint16_t BACK_COLOR;			//背景颜色定义

//LCD的宽和高的定义
#define	LCD_Width			320
#define	LCD_Height		170

//LCD的宽和高的定义
#define	LCD_Width			320
#define	LCD_Height		170

//Brush color
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 		0x001F  
#define BRED             0XF81F
#define GRED 			 				0XFFE0
#define GBLUE				 			0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0 //黄色
#define BROWN 		 				0XBC40 //棕色
#define BRRED 					 0XFC07 //棕红色
#define GRAY  					 0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 					 0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

/*
	LCD_RST:	PC10
	LCD_PWR:	PC11
	LCD_DC:		PA15
*/
#define	LCD_PWR(n)		(n?gpio_bit_set(GPIOC,GPIO_PIN_11):gpio_bit_reset(GPIOA,GPIO_PIN_11));
#define	LCD_RST(n)		(n?gpio_bit_set(GPIOC,GPIO_PIN_10):gpio_bit_reset(GPIOA,GPIO_PIN_10));
#define	LCD_DC(n)			(n?gpio_bit_set(GPIOA,GPIO_PIN_15):gpio_bit_reset(GPIOA,GPIO_PIN_15));

void Dri_LCD_Init(void);
void Dri_LCD_DisplayOn(void);
void Dri_LCD_DisplayOff(void);
void Dri_LCD_Gpio_Init();
void Dri_LCD_SPI_Send(uint8_t data);
void Dri_LCD_Write_Cmd(uint8_t cmd);
void Dri_LCD_Write_Data(uint8_t data);
void Dri_LCD_Write_HalfWord(uint16_t da);
void Dri_LCD_Clear(uint16_t color);
void Dri_LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);

#endif