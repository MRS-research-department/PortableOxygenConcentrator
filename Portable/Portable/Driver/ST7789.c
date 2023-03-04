#include "ST7789.h"

void LCD_Init(void)		//LCD屏初始化
{
	LCD_GPIO_Init(); 
	
	LCD_BL(1);//初始化时背光要关掉 以免显示杂色
	
	LCD_CS(0);
	
	LCD_RST(1);
	LCD_RST(0);
	LCD_RST(1);
	
	LCD_RST(0);
	delay_1ms(120);
	LCD_RST(1);	

	delay_1ms(120);                //Delay 120ms

	/* Sleep Out */
	LCD_Write_Cmd(0x11);     
	/* wait for power stability */
	delay_1ms(120);                 //Delay 120ms

	/* Memory Data Access Control */
	LCD_Write_Cmd(0x36);     
	LCD_Write_Data(0xA0);   

	/* RGB 5-6-5-bit  */
	LCD_Write_Cmd(0x3A);     
	LCD_Write_Data(0x05);   

	/* Porch Setting */
	LCD_Write_Cmd(0xB2);     
	LCD_Write_Data(0x0C);   
	LCD_Write_Data(0x0C);   
	LCD_Write_Data(0x00);   
	LCD_Write_Data(0x33);   
	LCD_Write_Data(0x33);   

	/*  Gate Control */
	LCD_Write_Cmd(0xB7);     
	LCD_Write_Data(0x72);   

	/* VCOM Setting */
	LCD_Write_Cmd(0xBB);     
	LCD_Write_Data(0x3D);   

	/* LCM Control */
	LCD_Write_Cmd(0xC0);     
	LCD_Write_Data(0x2C);   

	/* VDV and VRH Command Enable */
	LCD_Write_Cmd(0xC2);     
	LCD_Write_Data(0x01);   

	/* VRH Set */
	LCD_Write_Cmd(0xC3);     
	LCD_Write_Data(0x19);   

	/* VDV Set */
	LCD_Write_Cmd(0xC4);     
	LCD_Write_Data(0x20);   

	/* Frame Rate Control in Normal Mode */
	LCD_Write_Cmd(0xC6);     
	LCD_Write_Data(0x0F);   

	/* Power Control 1 */
	LCD_Write_Cmd(0xD0);     
	LCD_Write_Data(0xA4);   
	LCD_Write_Data(0xA1);   


	/* Positive Voltage Gamma Control */
	LCD_Write_Cmd(0xE0);
	LCD_Write_Data(0xD0);
	LCD_Write_Data(0x04);
	LCD_Write_Data(0x0D);
	LCD_Write_Data(0x11);
	LCD_Write_Data(0x13);
	LCD_Write_Data(0x2B);
	LCD_Write_Data(0x3F);
	LCD_Write_Data(0x54);
	LCD_Write_Data(0x4C);
	LCD_Write_Data(0x18);
	LCD_Write_Data(0x0D);
	LCD_Write_Data(0x0B);
	LCD_Write_Data(0x1F);
	LCD_Write_Data(0x23);
		
	/* Negative Voltage Gamma Control */
	LCD_Write_Cmd(0xE1);
	LCD_Write_Data(0xD0);
	LCD_Write_Data(0x04);
	LCD_Write_Data(0x0C);
	LCD_Write_Data(0x11);
	LCD_Write_Data(0x13);
	LCD_Write_Data(0x2C);
	LCD_Write_Data(0x3F);
	LCD_Write_Data(0x44);
	LCD_Write_Data(0x51);
	LCD_Write_Data(0x2F);
	LCD_Write_Data(0x1F);
	LCD_Write_Data(0x1F);
	LCD_Write_Data(0x20);
	LCD_Write_Data(0x23);  

  /* Display Inversion On */
	LCD_Write_Cmd(0x21);

	LCD_Write_Cmd(0x29);

	LCD_Address_Set(0, 0, LCD_Width - 1, LCD_Height - 1);

	LCD_Clear(BACK_COLOR);
	/*打开显示*/
	LCD_DisplayOn();
	
	 
}
