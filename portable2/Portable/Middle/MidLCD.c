#include "MidLCD.h"
#


/**
 * @brief	Middle��LCD��ʼ��
 *
 * @param   void
 *
 * @return  void
 */
void Mid_LCD_Init()
{
	void Dri_LCD_Init();
}

void Mid_LCD_Clear(uint16_t color)
{
	Dri_LCD_Clear(color);
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
/**************************************************************
�������� : lcd_show_char
�������� : lcd��ʾһ���ַ�
������� : x,y:��ʼ����
		   num:Ҫ��ʾ���ַ�:" "--->"~"
		   size:�����С
		   mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
����ֵ  	 : ��
��ע		 : ��
**************************************************************/
void Mid_LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode)
{  							  
  uint16_t temp, t1, t;
	uint16_t y0 = y;
	uint16_t csize = ((size / 8) + ((size % 8) ? 1 : 0)) * (size/2);	/* �õ�����һ���ַ���Ӧ������ռ���ֽ���	 */
	
 	num = num - ' ';	/* �õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩ */
	
	for(t = 0; t < csize; t++)	/*������ӡ�������ص㵽LCD */
	{   
     	if(16 == size)
		{
			temp = asc2_1608[num][t];	/* ����1608���� */
     	}
		else if(24 == size)
		{
			temp = asc2_2412[num][t];	/* ����2412���� */
		}
		else if(32 == size)
		{
			temp = asc2_3216[num][t];	/* ����3216��������� */
		}
		else
		{	
			return;		/* û���ҵ���Ӧ���ֿ� */
		}
		for(t1 = 0; t1 < 8; t1++)	/* ��ӡһ�����ص㵽Һ�� */
		{			    
			if(temp & 0x80)
			{
				Dri_LCD_Draw_Point(x, y, POINT_COLOR);
			}
			else if(0 == mode)
			{
				Dri_LCD_Draw_Point(x, y, BACK_COLOR);
			}
			temp <<= 1;
			y++;
			
			if(y >= LCD_Height)
			{
				return;		/* �������� */
			}
			if((y - y0) == size)
			{
				y = y0;
				x++;
//				if(x >= LCD_Width)
//				{
//					return;	/* �������� */
//				}
				break;
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
/**************************************************************
�������� : lcd_show_string
�������� : lcd��ʾ�ַ���
������� : x,y:��ʼ����
		   width,height�������С
		   *p:�ַ�����ʼ��ַ
		   size:�����С
		   mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
����ֵ  	 : ��
��ע		 : ��
**************************************************************/
void Mid_LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *p, uint8_t size, uint8_t mode)
{         
	uint16_t x0 = x;
	width += x;
	height += y;
	
    while((*p<='~') && (*p>=' '))		/* �ж��ǲ��ǷǷ��ַ�! */
    {       
        if(x >= width)
				{
					x = x0; 
					y += size;
				}
				
				 if(y >= height)
				 {	
					break;
				 }
        Mid_LCD_ShowChar(x, y, *p, size, mode);
        x += size/2;
        p++;
    }  
}

//unsigned int Concentration_old = 999;
//Ũ��
void Mid_Disp_Concentration(unsigned int x,unsigned int y,unsigned int temp)
{
	
	  unsigned char disp[5];
	
	  if(temp > 999) temp = 999;
	
	  //if(Concentration_old != temp )
		//{
		//	 Concentration_old = temp;
			 
			if(temp/100 == 0)
				disp[0] = ' '; 
			else
			 disp[0] = temp/100 + 0x30; 
			
			 disp[1] = temp%100/10 +0x30;  
			 disp[2] = ' '; 
			 disp[3] = '%';	
			 disp[4] =  '\0';
			
			 Mid_LCD_ShowString(x,y,120,12,disp,24,0);
	//	}	
}

void Mid_Window(void)
{
	Mid_Disp_Concentration(5,10,O2_concent);
}