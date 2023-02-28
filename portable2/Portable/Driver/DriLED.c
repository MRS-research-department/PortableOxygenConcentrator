#include "DriLED.h"

/**
 * @brief	LED���ƽӿڳ�ʼ��
 *
 * @param   void
 *
 * @return  void
 */
void Dri_LED_Gpio_Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOC);  //PCʱ��ʹ��
	
	gpio_init(LED_PORT,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,LED_PIN);		//PC1�����������
		
	gpio_bit_reset(LED_PORT,LED_PIN);		//��PC1�����õ�
	
}

