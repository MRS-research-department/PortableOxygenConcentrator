#include "DriKey.h"

/*
* ��    �ƣ�Mid_Key_Gpio_Init(void)
* ��    �ܣ��������ų�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵    ������
* ���÷������� 
*/
void Dir_Key_Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	
	gpio_init(GPIOA,GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
	gpio_init(GPIOB,GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);
}

/*
* ��    �ƣ�Mid_Key4(void)
* ��    �ܣ��жϰ����ĸߵ͵�ƽ
* ��ڲ�������
* ���ڲ�����SET �����������Ϊ����ֵ�棬 RESET  ����û���·���ֵΪ��
* ˵    ������
* ���÷������� 
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