#include "MidKey.h"
#include "DriKey.h"

static uint8_t Key4_Pressed = RESET;	   	//当前按键状态
static uint8_t Key4_Last_Pressed  = RESET;	//上次按键状态
uint8_t Key4_Status = RESET;				
uint8_t Start_Up = RESET;


void MidKey_Init()
{
	Dir_Key_Init();
}



void MidKey()
{
				if(Key4_Status == SET)
				{
				Key4_Pressed = SET;

				if((Key4_Last_Pressed  == RESET) && (Key4_Pressed == SET) )// 按键按下一瞬间
				{
					Key4_Last_Pressed  = Key4_Pressed;
					Start_Up ^= 0X01;
				}			
				}
				else{
					Key4_Last_Pressed = RESET;
					Key4_Pressed = RESET;

				}

}