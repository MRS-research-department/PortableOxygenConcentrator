#include "MidLED.h"
#include "DriLED.h"

/**
 * @brief	LED��ʼ��
 *
 * @param   void
 *
 * @return  void
 */
void Mid_LED_Init()
{
	Dri_LED_Gpio_Init();
}

/**
 * @brief	LED����˸
 *
 * @param   void
 *
 * @return  void
 */
void Mid_LED_Blink()
{
	LED(1);
	delay_1ms(500);
	
	LED(0);
	delay_1ms(500);
}