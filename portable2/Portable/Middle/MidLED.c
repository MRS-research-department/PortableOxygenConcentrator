#include "MidLED.h"
#include "DriLED.h"

/**
 * @brief	LED≥ı ºªØ
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
 * @brief	LEDµ∆…¡À∏
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