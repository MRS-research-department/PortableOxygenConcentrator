/**
  ******************************************************************************
  * @file    Appmain.c
  * @author  Medris R&D
  * @version V1.0.0
  * @date    1-March-2023
  * @brief   This file provides all the main functions. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2023 Medris R&D
  ******************************************************************************
  */
	
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

/******************* (C) COPYRIGHT 2023 Medris R&D *****END OF FILE****/
