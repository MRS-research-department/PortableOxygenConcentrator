#include "LCD.h"

uint16_t	POINT_COLOR = BLUE;	//������ɫ	Ĭ��Ϊ��ɫ
uint16_t	BACK_COLOR 	= LGRAYBLUE;	//������ɫ	Ĭ��Ϊ��ɫ

/**
 * @brief	LCD���ƽӿڳ�ʼ��
 *
 * @param   void
 *
 * @return  void
 */
void LCD_GPIO_Init(void){
		spi_parameter_struct spi_init_struct;
	
		rcu_periph_clock_enable(RCU_GPIOA);
		rcu_periph_clock_enable(RCU_GPIOB);
		rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_SPI0);
		
		rcu_periph_clock_enable(RCU_AF);
	
	  /* ʹ��SW����,��ʹ��JTAG����,�ܽ������������� */
	  gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);
	
		gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);// LCD DC
		gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);// LCD SDA
		gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_15);//LCD SCL
		gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_3);//LCD BL
		gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_10);//LCD RES
		gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_11);//LCD CS

//		gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);// LCD SCL
//		gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);// LCD SDA
//		 /* SPI��������*/
//    spi_init_struct.device_mode          = SPI_MASTER;
//		spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
//    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
//    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_1EDGE;
//    spi_init_struct.nss                  = SPI_NSS_SOFT;
//    spi_init_struct.prescale             = SPI_PSC_8 ;
//    spi_init_struct.endian               = SPI_ENDIAN_MSB;
//		
//    spi_init(SPI0, &spi_init_struct);
//		
//		spi_crc_polynomial_set(SPI0,8);
//		
//		spi_enable(SPI0);/*ʹ��SPI0*/
		
}


/**
* @brief	LCD�ײ�SPI�������ݺ���
*
* @param   data	���ݵ���ʼ��ַ
*
* @return  void
*/

void LCD_SPI_Send(uint8_t data)
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

//void LCD_SPI_Send(uint8_t data)
//{
//	uint8_t retry=10;	
//	
//	LCD_CS(0);
//	
//	while(spi_i2s_flag_get(SPI0,SPI_FLAG_TBE)==RESET){
//	};
//	spi_i2s_data_transmit(SPI0,data);	

//	LCD_CS(1);
//	
//}

/**
 * @brief	д���LCD
 *
 * @param   cmd		��Ҫ���͵�����
 *
 * @return  void
 */
void LCD_Write_Cmd(uint8_t cmd)
{
    LCD_DC(0);

    LCD_SPI_Send(cmd);
}

/**
 * @brief	д���ݵ�LCD
 *
 * @param   cmd		��Ҫ���͵�����
 *
 * @return  void
 */
void LCD_Write_Data(uint8_t data)
{
    LCD_DC(1);

    LCD_SPI_Send(data);
}


/**
 * @brief	д����ֵ����ݵ�LCD
 *
 * @param   da		��Ҫ���͵�����
 *
 * @return  void
 */
void LCD_Write_HalfWord(uint16_t da)
{
	LCD_DC(1);
	LCD_Write_Data(da>>8);
	LCD_Write_Data(da&0Xff);
}

/**
 * ��������д��LCD��������
 *
 * @param   x1,y1	�������
 * @param   x2,y2	�յ�����
 *
 * @return  void
 */
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
//    LCD_Write_Cmd(0x2a);
//    LCD_Write_Data(x1 >> 8);
//    LCD_Write_Data(x1);
//    LCD_Write_Data(x2 >> 8);
//    LCD_Write_Data(x2);

//    LCD_Write_Cmd(0x2b);
//    LCD_Write_Data(y1 >> 8);
//    LCD_Write_Data(y1);
//    LCD_Write_Data(y2 >> 8);
//    LCD_Write_Data(y2);

//    LCD_Write_Cmd(0x2C);
	
	
  if(USE_HORIZONTAL==0)   //����
	{
		LCD_Write_Cmd(0x2a);//�е�ַ����
		LCD_Write_Data((x1+35) >> 8);
	  LCD_Write_Data(x1+35);
	  LCD_Write_Data((x2+35)>>8);
		LCD_Write_Data(x2+35);
		LCD_Write_Cmd(0x2b);//�е�ַ����
    LCD_Write_Data(y1 >> 8);
    LCD_Write_Data(y1);
    LCD_Write_Data(y2 >> 8);
    LCD_Write_Data(y2);
		
		LCD_Write_Cmd(0x2c);//������д	
	}
	else if(USE_HORIZONTAL == 1) //����
	{
		LCD_Write_Cmd(0x2a);//�е�ַ����
		LCD_Write_Data(x1>>8);
	  LCD_Write_Data(x1);
	  LCD_Write_Data(x2>>8);
		LCD_Write_Data(x2);
	
		LCD_Write_Cmd(0x2b);//�е�ַ����
    LCD_Write_Data((y1+35) >> 8);
    LCD_Write_Data(y1+35);
    LCD_Write_Data((y2+35) >> 8);
    LCD_Write_Data(y2+35);
		
		LCD_Write_Cmd(0x2c);//������д			
	}
}

/**
 * ��LCD��ʾ
 *
 * @param   void
 *
 * @return  void
 */
void LCD_DisplayOn(void)
{
   // LCD_BL(1);
	 LCD_Write_Cmd(0x29);
}

/**
 * �ر�LCD��ʾ
 *
 * @param   void
 *
 * @return  void
 */
void LCD_DisplayOff(void)
{
   // LCD_BL(0);
	 LCD_Write_Cmd(0x28);
}

/**
 * ��һ����ɫ���LCD��
 *
 * @param   color	������ɫ
 *
 * @return  void
 */
void LCD_Clear(uint16_t color)
{
  uint16_t i, j;

	LCD_DisplayOff();		/* �ر���ʾ */
	
	if(USE_HORIZONTAL == 0)  //����
		LCD_Address_Set(0, 0, LCD_Width - 1, LCD_Height - 1);
	else if(USE_HORIZONTAL == 1) //����
		LCD_Address_Set(0, 0, LCD_Height - 1, LCD_Width - 1);	
	
	LCD_Write_Cmd(0x2C); 
	
	for(i = 0; i < LCD_Height; i++)    //LCD_Width
	{
		for(j = 0; j < LCD_Width; j++)  //LCD_Height
		{
			LCD_Write_Data(color >> 8);
			LCD_Write_Data(color & 0x00ff);
		}
	}
	
	LCD_DisplayOn();		/* ����ʾ */
}

/**
 * @brief	��ʾһ��ASCII���ַ�
 *
 * @param   x,y		��ʾ��ʼ����
 * @param   chr		��Ҫ��ʾ���ַ�
 * @param   size	�����С(֧��16/24/32������)
 *
 * @return  void
 */

void LCD_ShowChar(uint16_t x, uint16_t y, char chr, uint8_t size)
{
    uint8_t temp, t1, t;
    uint8_t csize;		//�õ�����һ���ַ���Ӧ������ռ���ֽ���
    uint16_t colortemp;
    uint8_t sta;

    chr = chr - ' '; //�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩

    if((x > (LCD_Width - size / 2)) || (y > (LCD_Height - size)))	return;

    LCD_Address_Set(x, y, x + size / 2 - 1, y + size - 1);//(x,y,x+8-1,y+16-1)

    if((size == 16) || (size == 32) )	//16��32������
    {
        csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);

        for(t = 0; t < csize; t++)
        {
            if(size == 16)temp = asc2_1608[chr][t];	//����1608����

            else if(size == 32)temp = asc2_3216[chr][t];	//����3216����

            else return;			//û�е��ֿ�

            for(t1 = 0; t1 < 8; t1++)
            {
                if(temp & 0x80) colortemp = POINT_COLOR;

                else colortemp = BACK_COLOR;

                LCD_Write_HalfWord(colortemp);
                temp <<= 1;
            }
        }
    }

	else if  (size == 12)	//12������
	{
        csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);

        for(t = 0; t < csize; t++)
        {
            temp = asc2_1206[chr][t];

            for(t1 = 0; t1 < 6; t1++)
            {
                if(temp & 0x80) colortemp = POINT_COLOR;

                else colortemp = BACK_COLOR;

                LCD_Write_HalfWord(colortemp);
                temp <<= 1;
            }
        }
    }
	
    else if(size == 24)		//24������
    {
        csize = (size * 16) / 8;

        for(t = 0; t < csize; t++)
        {
            temp = asc2_2412[chr][t];

            if(t % 2 == 0)sta = 8;

            else sta = 4;

            for(t1 = 0; t1 < sta; t1++)
            {
                if(temp & 0x80) colortemp = POINT_COLOR;

                else colortemp = BACK_COLOR;

                LCD_Write_HalfWord(colortemp);
                temp <<= 1;
            }
        }
    }
}



/**
 * @brief	��ʾ�ַ���
 *
 * @param   x,y		�������
 * @param   width	�ַ���ʾ������
 * @param   height	�ַ���ʾ����߶�
 * @param   size	�����С
 * @param   p		�ַ�����ʼ��ַ
 *
 * @return  void
 */
void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p)
{
	uint8_t x0 = x;
	width += x;
	height += y;

	while((*p <= '~') && (*p >= ' ')) //�ж��ǲ��ǷǷ��ַ�!
	{
		if(x >= width)
		{
				x = x0;
				y += size;
		}

		if(y >= height)break; //�˳�

		LCD_ShowChar(x, y, *p, size);
		x += size / 2;
		p++;
	}
}

