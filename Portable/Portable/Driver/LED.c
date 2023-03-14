#include "LED.h"

void LED_Init(void)
{
	rcu_adc_clock_config(RCU_AHB_CKSYS_DIV1);  //设置主频120M
	delay_1ms(100);

	rcu_periph_clock_enable(RCU_GPIOC);  //PC时钟使能

	rcu_periph_clock_enable(RCU_AF);

	gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_1);		//PC1配置推挽输出
	
	gpio_bit_reset(GPIOC,GPIO_PIN_1);				
}