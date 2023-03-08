
#ifndef LCD_H
#define LCD_H

#include "gd32f30x_gpio.h"
#include "Systick.h"
#include "ST7789.h"
#include "font.h"

extern		uint16_t	POINT_COLOR;
extern		uint16_t	BACK_COLOR;

//LCD的宽和高的定义
#define	LCD_Width			170
#define	LCD_Height		320

#define USE_HORIZONTAL 1

//Brush color
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0 //黄色
#define BROWN 		 	 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

/*
	LCD_RST:	PC10
	LCD_CS:	PC11
	LCD_DC:		PA15
*/
#define	LCD_CS(n)			(n?gpio_bit_set(GPIOC,GPIO_PIN_11):gpio_bit_reset(GPIOC,GPIO_PIN_11));//LCD CS
#define	LCD_RST(n)		(n?gpio_bit_set(GPIOC,GPIO_PIN_10):gpio_bit_reset(GPIOA,GPIO_PIN_10));//LCD RES
#define	LCD_DC(n)			(n?gpio_bit_set(GPIOA,GPIO_PIN_5):gpio_bit_reset(GPIOA,GPIO_PIN_5));//LCD DC
#define	LCD_BL(n)			(n?gpio_bit_set(GPIOB,GPIO_PIN_3):gpio_bit_reset(GPIOB,GPIO_PIN_3));//LCD BL
#define	LCD_SCL(n)		(n?gpio_bit_set(GPIOA,GPIO_PIN_15):gpio_bit_reset(GPIOA,GPIO_PIN_15));//LCD SCL
#define	LCD_SDA(n)		(n?gpio_bit_set(GPIOA,GPIO_PIN_7):gpio_bit_reset(GPIOA,GPIO_PIN_7));//LCD SDA

void LCD_Init(void);
void LCD_GPIO_Init(void);
void LCD_SPI_Send(uint8_t data);
void LCD_Write_Cmd(uint8_t cmd);
void LCD_Write_Data(uint8_t data);
void LCD_Write_HalfWord(uint16_t da);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Address_Set(uint16_t x1,uint16_t y,uint16_t x2,uint16_t y2);
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t chr, uint8_t size);
void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *p);
void LCD_Clear(uint16_t color);
void Disp_TimeCNT(unsigned int x,unsigned int y,unsigned int temp);
#endif

