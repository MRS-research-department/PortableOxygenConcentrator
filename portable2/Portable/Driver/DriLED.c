#include "DriLED.h"

/**
 * @brief	LED控制接口初始化
 *
 * @param   void
 *
 * @return  void
 */
void Dri_LED_Gpio_Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOC);  //PC时钟使能
	
	gpio_init(LED_PORT,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,LED_PIN);		//PC1配置推挽输出
		
	gpio_bit_reset(LED_PORT,LED_PIN);		//将PC1引脚置低
	
}

