
#ifndef LCD_H
#define LCD_H

#include "gd32f30x_gpio.h"
#include "Systick.h"
#include "ST7789.h"
#include "font.h"

extern		uint16_t	POINT_COLOR;
extern		uint16_t	BACK_COLOR;

//LCD�Ŀ�͸ߵĶ���
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
#define YELLOW        	 0xFFE0 //��ɫ
#define BROWN 		 	 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

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

