#include "DriKey.h"

/*
* 名    称：Mid_Key_Gpio_Init(void)
* 功    能：按键引脚初始化
* 入口参数：无
* 出口参数：无
* 说    明：无
* 调用方法：无 
*/
void Dir_Key_Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	
	gpio_init(GPIOA,GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
	gpio_init(GPIOB,GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);
}

/*
* 名    称：Mid_Key4(void)
* 功    能：判断按键的高低电平
* 入口参数：无
* 出口参数：SET 如果按键按下为返回值真， RESET  按键没按下返回值为假
* 说    明：无
* 调用方法：无 
*/
FlagStatus Dri_Key4(void)
{
	FlagStatus bit_status4;	
	
	bit_status4 = gpio_input_bit_get(GPIOA,GPIO_PIN_0);  //

	if(bit_status4 == RESET)
		return SET;
	else
		return RESET;
}