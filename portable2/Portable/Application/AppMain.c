#include "AppMain.h"


int main(void)
{
		systick_config();		//ʱ��ʹ��
		Mid_LED_Init();			//LED�Ƴ�ʼ������
	  Mid_LCD_Init();			//LCD��ʼ������
		Mid_LCD_Clear(WHITE);
	
		while(1){
			Mid_LED_Blink();	//LED����˸
		}
}

