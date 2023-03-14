#include "uart.h"

unsigned char UART0_Rxcount = 0;    //�������ݳ���
unsigned char UART0_Txcount = 0;		//�������ݳ���
unsigned char UART0_timeover = 0;   //uart0��ʱʱ��
unsigned char UART0_RxSuccess = 0;  //uart0���ճɹ�

unsigned char USART0TX_Buffer[15];
unsigned char USART0RX_Buffer[15];

unsigned char O2_gear = 2;
unsigned char O2_mode = 1;
unsigned int  O2_concent = 0;     //����Ũ��
unsigned char O2_number  = 30;    //ÿ���ӹ�����������Χ�޶� 4-40 �Σ��� 15-1.5 ��ÿ��


void USART0_config(void)
{
	  /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

	  rcu_periph_clock_enable(RCU_AF);
	
	 // gpio_pin_remap_config(GPIO_USART0_REMAP, ENABLE);  //remap ����0 ,����PB6,PB7ʱ��Ҫ
	
    /* connect port to USARTx_Tx */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    /* connect port to USARTx_Rx */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200U);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
		
		//usart_dma_transmit_config(USART0, USART_DENT_ENABLE);
    //usart_dma_receive_config(USART0, USART_DENR_ENABLE);
    usart_enable(USART0);

    /* ʹ��  USART0 ���ж� */
	  nvic_irq_enable(USART0_IRQn, 0, 1); 
			
			
	
   /* enable USART0 receive interrupt */
    usart_interrupt_enable(USART0, USART_INT_RBNE);
    
    /* enable USART0 transmit interrupt */
    //usart_interrupt_enable(USART0, USART_INT_TBE);s
}




/*USART�����ж�*/
void USART0_IRQHandler(void)
{

	 unsigned char temp;
	
	
	  if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))
		{
		  UART0_timeover = 0;//����ͨ�ų�ʱʱ�� 
		  temp = usart_data_receive(USART0);  //���ж�
		
			if(UART0_RxSuccess == 0)
			{
				/* receive data */
				USART0RX_Buffer[UART0_Rxcount] = temp; 
				
				UART0_Rxcount++;
				if(UART0_Rxcount >= 14)
				{
						UART0_RxSuccess = 1;
						UART0_Rxcount   = 0;
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

	
	USART0TX_Buffer[8] = '\0';
	UART0_SendByte(USART0TX_Buffer[0] );
	UART0_SendByte(USART0TX_Buffer[1] );		
	UART0_SendByte(USART0TX_Buffer[2] );
	UART0_SendByte(USART0TX_Buffer[3] );		
	UART0_SendByte(USART0TX_Buffer[4] );	
	UART0_SendByte(USART0TX_Buffer[5] );	
	UART0_SendByte(USART0TX_Buffer[6] );			
	UART0_SendByte(USART0TX_Buffer[7] );		
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
