/**/


#include "AppMain.h"


int main(void)
{
		systick_config();		//ʱ��ʹ��
		Mid_LED_Init();			//LED�Ƴ�ʼ������
		Mid_LCD_Init();			//LCD��ʼ������
		Mid_LCD_Clear(WHITE);
	
		while(1)
		{
			if( Start_Up == 0X01)
			{
				LCD_ShowString(5, 10, 12, 12, 12, 1);						
				bit_Valve = 1;
				motor_send[0] = 60;	
			}
			else
			{
				LCD_ShowString(5, 10, 12, 12, 12, 0); 
				motor_send[0] = 0;
				bit_Valve = 0;	
			}
		}
}

