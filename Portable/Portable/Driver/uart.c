#include "uart.h"

unsigned char UART0_Rxcount;    //接收数据长度
unsigned char UART0_timeover;   //uart0超时时间
unsigned char UART0_RxSuccess;  //uart0接收成功

unsigned char USART0TX_Buffer[15];
unsigned char USART0RX_Buffer[15];

#define USART0_RDATA_ADDRESS      ((uint32_t)&USART_DATA(USART0))

unsigned char O2_gear = 2;
unsigned char O2_mode = 1;
unsigned int  O2_concent = 0;     //氧气浓度
unsigned char O2_number  = 30;    //每分钟供气次数，范围限定 4-40 次，即 15-1.5 秒每次
unsigned char flow;
unsigned char mode;
unsigned char o2_flow;
unsigned char o2_temp;
unsigned char breez;
unsigned char hz;


void uart_init_config(void)
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
    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))//发送
		{
			UART0_timeover = 0;  //串口通信超时时间
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
	while(usart_flag_get(USART0, USART_FLAG_TBE) != SET) //发送缓冲区非空
	{	
	}

}

void UART0_PutString(char *str)
{

	while(*str != '\0')  //结束符
	{
		UART0_SendByte(*str);
		str++;
	}

}


/*读取氧浓度传感器数据*/
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
//	if((temp_u8==0) && (USART5RX_Buffer[0]==0x16) && (USART5RX_Buffer[1]==0x09) && (USART5RX_Buffer[2]==0x01)) //累加和为 0 
		if( (USART0RX_Buffer[0]==0x16) && (USART0RX_Buffer[1]==0x09) && (USART0RX_Buffer[2]==0x01))
		{
				 O2_concent = USART0RX_Buffer[3]*256 + USART0RX_Buffer[4]; //氧气浓度（o2_concent/10）%
			
				 flow = USART0RX_Buffer[5]; //档位
				 mode = USART0RX_Buffer[6]; //工作状态：关闭 0、随吸 1、直供 2
				 o2_flow = USART0RX_Buffer[7]; //实时流量（o2_flow/10）L/min 或单次供气量（o2_flow）ml
			 	 o2_temp = USART0RX_Buffer[8]; //氧气温度（o2_temp）℃
				 breez = USART0RX_Buffer[9];//呼吸标志
				 hz = USART0RX_Buffer[10]; //呼吸频率 hz/min
		}
			
	UART0_RxSuccess = 0;	
	}
	
}
