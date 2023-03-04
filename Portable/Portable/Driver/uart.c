#include "uart.h"




void uart_init()
{
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_USART0);
	rcu_periph_clock_enable(RCU_AF);
	
	/* ʹ��SW����,��ʹ��JTAG����,�ܽ������������� */
	gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);
	
	/* PB1  ����Ϊ USART0_Tx */
  gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_1);

  /* PB2 ����Ϊ USARTx_Rx */
  gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ,GPIO_PIN_2);
	 
    /* USART ���� */
    usart_deinit(USART0);//���ô���0
    usart_baudrate_set(USART0, 115200U);//���ô���0�Ĳ�����Ϊ115200
    usart_word_length_set(USART0, USART_WL_8BIT);      	// ֡�����ֳ�
		usart_stop_bit_set(USART0, USART_STB_1BIT);      	 	// ֹͣλ1λ
    usart_parity_config(USART0, USART_PM_NONE);       	// ����żУ��λ
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);//ʹ�ܽ�����
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);//ʹ�ܷ�����
    usart_enable(USART0);//ʹ��USART
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}

void uart_data_transmit(uint8_t arr[], uint32_t length) 
{
	uint32_t i;
	for(i=0; i<length; i++) 
	{
		usart_data_transmit(USART0, arr[i]);
		while (usart_flag_get(USART0, USART_FLAG_TBE)== RESET);
	}
}

