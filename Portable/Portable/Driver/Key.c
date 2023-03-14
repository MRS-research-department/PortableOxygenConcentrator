#include "Key.h"

void Key_GPIO_Init()
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	
	gpio_init(GPIOA,GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
	gpio_init(GPIOB,GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);	
}



FlagStatus Key4()
{
	FlagStatus bit_status4;	
	bit_status4 = gpio_input_bit_get(GPIOA,GPIO_PIN_0);

	if(bit_status4 == RESET)
		return SET;
	else
		return RESET;
}


