#include "DriLCD.h"

uint16_t	POINT_COLOR	=	BLACK;		//画笔颜色		默认黑色
uint16_t	BACK_COLOR	=	WHITE;		//背景颜色		默认白色

void Dri_LCD_Gpio_Init(void)
{
//	spi_parameter_struct spi_init_struct;
	
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_SPI0);

	rcu_periph_clock_enable(RCU_AF);

/* 使用SW下载,不使用JTAG下载,管脚用作其它功能 */
	gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);

	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);// LCD DC
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);// LCD SDA
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_15);//LCD SCL
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_3);//LCD BL
	gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_10);//LCD RES
	gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_11);//LCD CS

//	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);// LCD SCL
//	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);// LCD SDA
//		 /* SPI参数配置*/
//	spi_init_struct.device_mode          = SPI_MASTER;
//	spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
//	spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
//	spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_1EDGE;
//	spi_init_struct.nss                  = SPI_NSS_SOFT;
//	spi_init_struct.prescale             = SPI_PSC_8 ;
//	spi_init_struct.endian               = SPI_ENDIAN_MSB;
//		
//	spi_init(SPI0, &spi_init_struct);
//		
//	spi_crc_polynomial_set(SPI0,8);
//		
//	spi_enable(SPI0);/*使能SPI0*/
}

/*
函数名称 : lcd_draw_point
函数功能 : lcd画一个点
输入参数 : x,y	--> 画点坐标，color --> 点的颜色
返回值  	 : 无
备注		 : 无
**************************************************************/
void Dri_LCD_Draw_Point(uint16_t x, uint16_t y, uint16_t color)
{
	Dri_LCD_Address_Set(x, y, x, y);
	Dri_LCD_Write_Data(color >> 8);
    Dri_LCD_Write_Data(color & 0x00ff); 
}


/**
 * @brief	LCD底层SPI发送数据函数
 *
 * @param   data	数据的起始地址
 *
 * @return  void
 */
void Dri_LCD_SPI_Send(uint8_t data)
{
	LCD_CS(0);
	
	for(int i = 0; i < 8; i++)
	{	  
		LCD_SCL(0);
		
		if(data & 0x80){
			LCD_SDA(1);
		}
		else{
			LCD_SDA(0);			
		}
		
		LCD_SCL(1);
		
		data <<= 1;  
	}
	
	LCD_CS(1); 
}

/**
 * @brief	写命令到LCD
 *
 * @param   cmd		需要发送的命令
 *
 * @return  void
 */
void Dri_LCD_Write_Cmd(uint8_t cmd)
{
    LCD_DC(0);

    Dri_LCD_SPI_Send(cmd);
}

/**
 * @brief	写数据到LCD
 *
 * @param   cmd		需要发送的数据
 *
 * @return  void
 */
void Dri_LCD_Write_Data(uint8_t data)
{
    LCD_DC(1);

    Dri_LCD_SPI_Send(data);
}

/**
 * @brief	写半个字的数据到LCD
 *
 * @param   da		需要发送的数据
 *
 * @return  void
 */
void Dri_LCD_Write_HalfWord(uint16_t da)
{
	LCD_DC(1);
	Dri_LCD_Write_Data(da>>8);
	Dri_LCD_Write_Data(da&0xff);
}

/**
 * 打开LCD显示
 *
 * @param   void
 *
 * @return  void
 */
void Dri_LCD_DisplayOn(void)
{
	LCD_CS(1);
}

/**
 * 关闭LCD显示
 *
 * @param   void
 *
 * @return  void
 */
void Dri_LCD_DisplayOff(void)
{
	LCD_CS(0);
}

/**
 * 以一种颜色清空LCD屏
 *
 * @param   color	清屏颜色
 *
 * @return  void
 */
void Dri_LCD_Clear(uint16_t color)
{
	int i,j;
	for(i=0;i<170;i++)
	{
		for(j=0;j<320;j++)
		{
			Dri_LCD_Write_HalfWord(color);
		}
	}
}

/**
 * 设置数据写入LCD缓存区域
 *
 * @param   x1,y1	起点坐标
 * @param   x2,y2	终点坐标
 *
 * @return  void
 */
void Dri_LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	Dri_LCD_Write_Cmd(0x2A);     
	Dri_LCD_Write_Data(x1 >> 8);
	Dri_LCD_Write_Data(x1);
	Dri_LCD_Write_Data(x2 >> 8);
	Dri_LCD_Write_Data(x2);

	Dri_LCD_Write_Cmd(0x2b);
	Dri_LCD_Write_Data(y1 >> 8);
	Dri_LCD_Write_Data(y1);
	Dri_LCD_Write_Data(y2 >> 8);
	Dri_LCD_Write_Data(y2);   

	Dri_LCD_Write_Cmd(0x2C); 
}

/**
 * @brief	Driver层LCD初始化
 *
 * @param   void
 *
 * @return  void
 */
void Dri_LCD_Init(void)	
{
	Dri_LCD_Gpio_Init();  
	LCD_CS(0);
	LCD_RST(0);
	delay_1ms(120);
	LCD_RST(1);	

	delay_1ms(120);                //Delay 120ms

	/* Sleep Out */
	Dri_LCD_Write_Cmd(0x11);     
	/* wait for power stability */
	delay_1ms(120);                 //Delay 120ms

	/* Memory Data Access Control */
	Dri_LCD_Write_Cmd(0x36);     
	Dri_LCD_Write_Data(0x00);   

	/* RGB 5-6-5-bit  */
	Dri_LCD_Write_Cmd(0x3A);     
	Dri_LCD_Write_Data(0x06);   

	/* Porch Setting */
	Dri_LCD_Write_Cmd(0xB2);     
	Dri_LCD_Write_Data(0x0C);   
	Dri_LCD_Write_Data(0x0C);   
	Dri_LCD_Write_Data(0x00);   
	Dri_LCD_Write_Data(0x33);   
	Dri_LCD_Write_Data(0x33);   

	/*  Gate Control */
	Dri_LCD_Write_Cmd(0xB7);     
	Dri_LCD_Write_Data(0x35);   

	/* VCOM Setting */
	Dri_LCD_Write_Cmd(0xBB);     
	Dri_LCD_Write_Data(0x13);   

	/* LCM Control */
	Dri_LCD_Write_Cmd(0xC0);     
	Dri_LCD_Write_Data(0x2C);   

	/* VDV and VRH Command Enable */
	Dri_LCD_Write_Cmd(0xC2);     
	Dri_LCD_Write_Data(0x01);   

	/* VRH Set */
	Dri_LCD_Write_Cmd(0xC3);     
	Dri_LCD_Write_Data(0x0B);   

	/* VDV Set */
	Dri_LCD_Write_Cmd(0xC4);     
	Dri_LCD_Write_Data(0x20);   

	/* Frame Rate Control in Normal Mode */
	Dri_LCD_Write_Cmd(0xC6);     
	Dri_LCD_Write_Data(0x0F);   

	/* Power Control 1 */
	Dri_LCD_Write_Cmd(0xD0);     
	Dri_LCD_Write_Data(0xA4);   
	Dri_LCD_Write_Data(0xA1);   


	/* Positive Voltage Gamma Control */
	Dri_LCD_Write_Cmd(0xE0);     
	Dri_LCD_Write_Data(0x00);   
	Dri_LCD_Write_Data(0x03);   
	Dri_LCD_Write_Data(0x07);   
	Dri_LCD_Write_Data(0x08);   
	Dri_LCD_Write_Data(0x07);   
	Dri_LCD_Write_Data(0x15);   
	Dri_LCD_Write_Data(0x2A);   
	Dri_LCD_Write_Data(0x44);   
	Dri_LCD_Write_Data(0x42);   
	Dri_LCD_Write_Data(0x0A);   
	Dri_LCD_Write_Data(0x17);   
	Dri_LCD_Write_Data(0x18);   
	Dri_LCD_Write_Data(0x25);   
	Dri_LCD_Write_Data(0x27);   

	/* Negative Voltage Gamma Control */
	Dri_LCD_Write_Cmd(0xE1);     
	Dri_LCD_Write_Data(0x00);   
	Dri_LCD_Write_Data(0x03);   
	Dri_LCD_Write_Data(0x08);   
	Dri_LCD_Write_Data(0x07);   
	Dri_LCD_Write_Data(0x07);   
	Dri_LCD_Write_Data(0x23);   
	Dri_LCD_Write_Data(0x2A);   
	Dri_LCD_Write_Data(0x43);   
	Dri_LCD_Write_Data(0x42);   
	Dri_LCD_Write_Data(0x09);   
	Dri_LCD_Write_Data(0x18);   
	Dri_LCD_Write_Data(0x17);   
	Dri_LCD_Write_Data(0x25);   
	Dri_LCD_Write_Data(0x27);   

	/* Display Inversion On */
	Dri_LCD_Write_Cmd(0x21); 

	Dri_LCD_Write_Cmd(0x29);     

	Dri_LCD_Address_Set(0,0,LCD_Width-1,LCD_Height-1);

	Dri_LCD_Clear(WHITE);

	/* Display on */
	LCD_CS(1);
	delay_1ms(200);
}
