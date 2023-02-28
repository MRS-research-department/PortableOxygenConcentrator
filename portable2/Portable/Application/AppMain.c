#include "AppMain.h"


int main(void)
{
		systick_config();		//时钟使能
		Mid_LED_Init();			//LED灯初始化函数
	  Mid_LCD_Init();			//LCD初始化函数
		Mid_LCD_Clear(WHITE);
	
		while(1){
			Mid_LED_Blink();	//LED灯闪烁
		}
}

