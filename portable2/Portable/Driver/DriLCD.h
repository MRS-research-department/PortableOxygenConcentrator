#ifndef DIRLCD_H
#define DIRLCD_H

#include "gd32f30x_gpio.h"
#include "Systick.h"

extern uint16_t POINT_COLOR;		//������ɫ����
extern uint16_t BACK_COLOR;			//������ɫ����

//LCD�Ŀ�͸ߵĶ���
#define	LCD_Width			320
#define	LCD_Height		170

//LCD�Ŀ�͸ߵĶ���
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
#define YELLOW        	 0xFFE0 //��ɫ
#define BROWN 		 				0XBC40 //��ɫ
#define BRRED 					 0XFC07 //�غ�ɫ
#define GRAY  					 0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 					 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

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