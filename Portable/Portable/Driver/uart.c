#include "uart.h"

unsigned char UART0_Rxcount = 0;    //�������ݳ���
unsigned char UART0_Txcount = 0;		//�������ݳ���
unsigned char UART0_timeover = 0;   //uart0��ʱʱ��
unsigned char UART0_RxSuccess;  //uart0���ճɹ�

unsigned char USART0TX_Buffer[8];
unsigned char USART0RX_Buffer[15];

#define USART0_RDATA_ADDRESS      ((uint32_t)&USART_DATA(USART0))

unsigned char O2_gear = 2;
unsigned char O2_mode = 1;
unsigned int  O2_concent = 0;     //����Ũ��
unsigned char O2_number  = 30;    //ÿ���ӹ�����������Χ�޶� 4-40 �Σ��� 15-1.5 ��ÿ��


void uart_config(void)
{
  /* ʹ��GPI0A����PA9��PA10Ϊ���� */
    rcu_periph_clock_enable(RCU_GPIOA);

    /*ʹ�ܴ���0��ʱ�� */
    rcu_periph_clock_enable(RCU_USART0);

    /*����USARTx_Tx(PA9)Ϊ�����������*/
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
 
    /*����USARTx_RxPA9)Ϊ�������� */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

   /* USART ���� */
    usart_deinit(USART0);//���ô���0
    usart_baudrate_set(USART0, 115200U);//���ô���0�Ĳ�����Ϊ115200
    usart_word_length_set(USART0, USART_WL_8BIT);      	// ֡�����ֳ�
	usart_stop_bit_set(USART0, USART_STB_1BIT);      	 	// ֹͣλ1λ
    usart_parity_config(USART0, USART_PM_NONE);       	// ����żУ��λ
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);//ʹ�ܽ�����
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);//ʹ�ܷ�����
    usart_enable(USART0);//ʹ��USART
	
	/*����USART0�ж�*/
	nvic_irq_enable(USART0_IRQn,0,0);
	usart_interrupt_enable(USART0,USART_INT_TBE);
	usart_interrupt_enable(USART0, USART_INT_RBNE); 

}



void USART0_IRQHandler(void)
{
    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))//����
	{
		/* receive data */
			USART0RX_Buffer[UART0_Rxcount] = usart_data_receive(USART0);		
			if(UART0_Rxcount ==14)
			{
				usart_interrupt_disable(USART0,USART_INT_RBNE);
			}
	}
	if(RESET != usart_interrupt_flag_get(USART0,USART_INT_FLAG_TBE))
	{
		/* transmit data */
		usart_data_transmit(USART0,USART0RX_Buffer[UART0_Txcount++]);
		if(UART0_Txcount > 7)
		{
			usart_interrupt_disable(USART0,USART_INT_TBE);
		}
	}
} 

void uart_data_transmit(uint8_t arr[], uint32_t length) 
{
	uint32_t i;
	for(i=0; i<length; i++) 
	{
		usart_data_transmit(USART0, arr[i]);
		while (usart_flag_get(USART0, USART_FLAG_TBE)== RESET);
	}
	delay_1ms(1000);
}


void UART0_Send_O2CMD(void)
{
	unsigned char temp;
	unsigned char i;
	uint32_t len;

	USART0TX_Buffer[0] = 0x16;
	USART0TX_Buffer[1] = 0x09;
	USART0TX_Buffer[2] = 0x01;
	USART0TX_Buffer[3] = O2_gear;    //������ 5 ������Ӧ���ι��������5x12=60mL��
	USART0TX_Buffer[4] = O2_mode;    //����ģʽ���������ر� 0������ 1��ֱ�� 2��
	USART0TX_Buffer[5] = O2_number;  //ÿ���ӹ�������
	USART0TX_Buffer[6] = 0x0C; //������

	temp = 0;     //����
	for(i=0; i<7; i++)   //����У��λ
	{
	temp += USART0TX_Buffer[i];  //ע temp Ϊ 8 λ�޷�����
	}
	USART0TX_Buffer[7] = 0x00 - temp;
	len = sizeof(USART0TX_Buffer) / sizeof(*(USART0TX_Buffer));
	uart_data_transmit(USART0TX_Buffer, len);

	
//  USART0TX_Buffer[8] = '\0';
//	UART5_PutString(USART5TX_Buffer);
//	UART0_SendByte(USART0TX_Buffer[0] );
//	UART0_SendByte(USART0TX_Buffer[1] );		
//	UART0_SendByte(USART0TX_Buffer[2] );
//	UART0_SendByte(USART0TX_Buffer[3] );		
//	UART0_SendByte(USART0TX_Buffer[4] );	
//	UART0_SendByte(USART0TX_Buffer[5] );	
//	UART0_SendByte(USART0TX_Buffer[6] );			
//	UART0_SendByte(USART0TX_Buffer[7] );		
}


/*--------------����������������-------------------------------------------------*/
void UART0_O2_para(void)
{
	unsigned char temp_u8;
	unsigned char i;


	 temp_u8 = 0;

	 if(UART0_RxSuccess)
		{
			for(i=0;i<14;i++)
			{		 
				temp_u8 += USART0RX_Buffer[i];
			}
		
		//	if((temp_u8==0) && (USART5RX_Buffer[0]==0x16) && (USART5RX_Buffer[1]==0x09) && (USART5RX_Buffer[2]==0x01)) //�ۼӺ�Ϊ 0 
			if( (USART0RX_Buffer[0]==0x16) && (USART0RX_Buffer[1]==0x09) && (USART0RX_Buffer[2]==0x01))
			{
				 O2_concent = USART0RX_Buffer[3]*256 + USART0RX_Buffer[4]; //����Ũ�ȣ�o2_concent/10��%
			
	//				 flow = USART2_RXbuffer[5]; //��λ
	//				 mode = USART2_RXbuffer[6]; //����״̬���ر� 0������ 1��ֱ�� 2
	//				 o2_flow = USART2_RXbuffer[7] //ʵʱ������o2_flow/10��L/min �򵥴ι�������o2_flow��ml
	//			 	 o2_temp = USART2_RXbuffer[8]; //�����¶ȣ�o2_temp����
	//				 breez = USART2_RXbuffer[9];//������־
	//				 hz = USART2_RXbuffer[10]; //����Ƶ�� hz/min
			}
			
			
			UART0_RxSuccess = 0;	
		}	
	
}