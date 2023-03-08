#include "uart.h"

unsigned char UART0_Rxcount;    //�������ݳ���
unsigned char UART0_timeover;   //uart0��ʱʱ��
unsigned char UART0_RxSuccess;  //uart0���ճɹ�

unsigned char USART0TX_Buffer[15];
unsigned char USART0RX_Buffer[15];

#define USART0_RDATA_ADDRESS      ((uint32_t)&USART_DATA(USART0))

unsigned char O2_gear = 2;
unsigned char O2_mode = 1;
unsigned int  O2_concent = 0;     //����Ũ��
unsigned char O2_number  = 30;    //ÿ���ӹ�����������Χ�޶� 4-40 �Σ��� 15-1.5 ��ÿ��
unsigned char flow;
unsigned char mode;
unsigned char o2_flow;
unsigned char o2_temp;
unsigned char breez;
unsigned char hz;


void uart_init_config(void)
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
	nvic_irq_enable(USART0_IRQn,0,1);
	usart_interrupt_enable(USART0,USART_INT_TBE);
	delay_1ms(1000);
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}


void USART0_IRQHandler(void)
{
	unsigned char temp;
	temp = usart_data_receive(USART0);
    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))//����
		{
			UART0_timeover = 0;  //����ͨ�ų�ʱʱ��
			if(UART0_RxSuccess == 0)
			{
				USART0RX_Buffer[UART0_Rxcount] = temp;
				
				UART0_Rxcount++;
				if(UART0_Rxcount > 14)
				{
					UART0_Rxcount = 0;
					UART0_RxSuccess = 1;
				}
			}
        }
    
}

/*--------------------------------------------------------------
**function:     void UART1_SendByte(unsigned char tdata)
**description:  
**parameter:      
**return:          
----------------------------------------------------------------*/
void UART0_SendByte(unsigned char tdata)
{
	usart_data_transmit(USART0, tdata);
	while(usart_flag_get(USART0, USART_FLAG_TBE) != SET) //���ͻ������ǿ�
	{	
	}

}

void UART0_PutString(char *str)
{

	while(*str != '\0')  //������
	{
		UART0_SendByte(*str);
		str++;
	}

}


/*��ȡ��Ũ�ȴ���������*/
void UART_O2_Pare(void)
{
	
	unsigned char i;
	unsigned char temp_u8;
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
			
				 flow = USART0RX_Buffer[5]; //��λ
				 mode = USART0RX_Buffer[6]; //����״̬���ر� 0������ 1��ֱ�� 2
				 o2_flow = USART0RX_Buffer[7]; //ʵʱ������o2_flow/10��L/min �򵥴ι�������o2_flow��ml
			 	 o2_temp = USART0RX_Buffer[8]; //�����¶ȣ�o2_temp����
				 breez = USART0RX_Buffer[9];//������־
				 hz = USART0RX_Buffer[10]; //����Ƶ�� hz/min
		}
			
	UART0_RxSuccess = 0;	
	}
	
}
