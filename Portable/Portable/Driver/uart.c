#include "uart.h"

unsigned char UART0_Rxcount = 0;    //接收数据长度
unsigned char UART0_Txcount = 0;		//发送数据长度
unsigned char UART0_timeover = 0;   //uart0超时时间
unsigned char UART0_RxSuccess;  //uart0接收成功

unsigned char USART0TX_Buffer[8];
unsigned char USART0RX_Buffer[15];

#define USART0_RDATA_ADDRESS      ((uint32_t)&USART_DATA(USART0))

unsigned char O2_gear = 2;
unsigned char O2_mode = 1;
unsigned int  O2_concent = 0;     //氧气浓度
unsigned char O2_number  = 30;    //每分钟供气次数，范围限定 4-40 次，即 15-1.5 秒每次


void uart_config(void)
{
  /* 使能GPI0A，用PA9、PA10为串口 */
    rcu_periph_clock_enable(RCU_GPIOA);

    /*使能串口0的时钟 */
    rcu_periph_clock_enable(RCU_USART0);

    /*配置USARTx_Tx(PA9)为复用推挽输出*/
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
 
    /*配置USARTx_RxPA9)为浮空输入 */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

   /* USART 配置 */
    usart_deinit(USART0);//重置串口0
    usart_baudrate_set(USART0, 115200U);//设置串口0的波特率为115200
    usart_word_length_set(USART0, USART_WL_8BIT);      	// 帧数据字长
	usart_stop_bit_set(USART0, USART_STB_1BIT);      	 	// 停止位1位
    usart_parity_config(USART0, USART_PM_NONE);       	// 无奇偶校验位
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);//使能接收器
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);//使能发送器
    usart_enable(USART0);//使能USART
	
	/*开启USART0中断*/
	nvic_irq_enable(USART0_IRQn,0,0);
	usart_interrupt_enable(USART0,USART_INT_TBE);
	usart_interrupt_enable(USART0, USART_INT_RBNE); 

}



void USART0_IRQHandler(void)
{
    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))//发送
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
	USART0TX_Buffer[3] = O2_gear;    //即脉冲 5 档，对应单次供气体积：5x12=60mL。
	USART0TX_Buffer[4] = O2_mode;    //供氧模式（传感器关闭 0、脉冲 1、直供 2）
	USART0TX_Buffer[5] = O2_number;  //每分钟供气次数
	USART0TX_Buffer[6] = 0x0C; //灵敏度

	temp = 0;     //清零
	for(i=0; i<7; i++)   //计算校验位
	{
	temp += USART0TX_Buffer[i];  //注 temp 为 8 位无符号型
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


/*--------------读氧气传感器数据-------------------------------------------------*/
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
		
		//	if((temp_u8==0) && (USART5RX_Buffer[0]==0x16) && (USART5RX_Buffer[1]==0x09) && (USART5RX_Buffer[2]==0x01)) //累加和为 0 
			if( (USART0RX_Buffer[0]==0x16) && (USART0RX_Buffer[1]==0x09) && (USART0RX_Buffer[2]==0x01))
			{
				 O2_concent = USART0RX_Buffer[3]*256 + USART0RX_Buffer[4]; //氧气浓度（o2_concent/10）%
			
	//				 flow = USART2_RXbuffer[5]; //档位
	//				 mode = USART2_RXbuffer[6]; //工作状态：关闭 0、随吸 1、直供 2
	//				 o2_flow = USART2_RXbuffer[7] //实时流量（o2_flow/10）L/min 或单次供气量（o2_flow）ml
	//			 	 o2_temp = USART2_RXbuffer[8]; //氧气温度（o2_temp）℃
	//				 breez = USART2_RXbuffer[9];//呼吸标志
	//				 hz = USART2_RXbuffer[10]; //呼吸频率 hz/min
			}
			
			
			UART0_RxSuccess = 0;	
		}	
	
}