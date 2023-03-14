#include "MidLCD.h"
#


/**
 * @brief	Middle层LCD初始化
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
 * @brief	显示一个ASCII码字符
 *
 * @param   x,y		显示起始坐标
 * @param   chr		需要显示的字符
 * @param   size	字体大小(支持16/24/32号字体)
 *
 * @return  void
 */
/**************************************************************
函数名称 : lcd_show_char
函数功能 : lcd显示一个字符
输入参数 : x,y:起始坐标
		   num:要显示的字符:" "--->"~"
		   size:字体大小
		   mode:叠加方式(1)还是非叠加方式(0)
返回值  	 : 无
备注		 : 无
**************************************************************/
void Mid_LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode)
{  							  
  uint16_t temp, t1, t;
	uint16_t y0 = y;
	uint16_t csize = ((size / 8) + ((size % 8) ? 1 : 0)) * (size/2);	/* 得到字体一个字符对应点阵集所占的字节数	 */
	
 	num = num - ' ';	/* 得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库） */
	
	for(t = 0; t < csize; t++)	/*遍历打印所有像素点到LCD */
	{   
     	if(16 == size)
		{
			temp = asc2_1608[num][t];	/* 调用1608字体 */
     	}
		else if(24 == size)
		{
			temp = asc2_2412[num][t];	/* 调用2412字体 */
		}
		else if(32 == size)
		{
			temp = asc2_3216[num][t];	/* 调用3216数码管字体 */
		}
		else
		{	
			return;		/* 没有找到对应的字库 */
		}
		for(t1 = 0; t1 < 8; t1++)	/* 打印一个像素点到液晶 */
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
				return;		/* 超区域了 */
			}
			if((y - y0) == size)
			{
				y = y0;
				x++;
//				if(x >= LCD_Width)
//				{
//					return;	/* 超区域了 */
//				}
				break;
			}
		}  	 
	}  	    	   	 	  
} 	

/**
 * @brief	显示字符串
 *
 * @param   x,y		起点坐标
 * @param   width	字符显示区域宽度
 * @param   height	字符显示区域高度
 * @param   size	字体大小
 * @param   p		字符串起始地址
 *
 * @return  void
 */
/**************************************************************
函数名称 : lcd_show_string
函数功能 : lcd显示字符串
输入参数 : x,y:起始坐标
		   width,height：区域大小
		   *p:字符串起始地址
		   size:字体大小
		   mode:叠加方式(1)还是非叠加方式(0)
返回值  	 : 无
备注		 : 无
**************************************************************/
void Mid_LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *p, uint8_t size, uint8_t mode)
{         
	uint16_t x0 = x;
	width += x;
	height += y;
	
    while((*p<='~') && (*p>=' '))		/* 判断是不是非法字符! */
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
//浓度
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