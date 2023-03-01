#include "DriLCD.h"

uint16_t	POINT_COLOR	=	BLACK;		//画笔颜色		默认黑色
uint16_t	BACK_COLOR	=	WHITE;		//背景颜色		默认白色

void Dri_LCD_Gpio_Init(void)
{
	spi_parameter_struct	spi_init_strcut;
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_SPI0);

	//
	gpio_init(GPIOA,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_5 | GPIO_PIN_7);
	gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_10 | GPIO_PIN_11);
	gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_15);

	//SPI参数配置
	spi_init_strcut.trans_mode						=SPI_TRANSMODE_FULLDUPLEX;
	spi_init_strcut.device_mode						=SPI_MASTER;
	spi_init_strcut.frame_size						=SPI_FRAMESIZE_8BIT;
	spi_init_strcut.clock_polarity_phase	=SPI_CK_PL_HIGH_PH_1EDGE;
	spi_init_strcut.nss										=SPI_NSS_SOFT;
	spi_init_strcut.prescale 							=SPI_PSC_8;
	spi_init_strcut.endian								=SPI_ENDIAN_MSB;
	spi_init(SPI0,&spi_init_strcut);

	//
	spi_crc_polynomial_set(SPI0,8);
	//使能SPI0
	spi_enable(SPI0);

	LCD_RST(1);
	delay_1ms(100);
	LCD_RST(0);
	delay_1ms(100);
	LCD_RST(1);
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
	uint8_t retry=0;
	spi_i2s_data_transmit(SPI0,data);  
	while(spi_i2s_flag_get(SPI0,SPI_FLAG_TBE)==RESET){
	};
	for(retry=0;retry<10;retry++); 
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
	LCD_PWR(1);
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
	LCD_PWR(0);
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
	LCD_PWR(0);
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
	LCD_PWR(1);
	delay_1ms(200);
}
