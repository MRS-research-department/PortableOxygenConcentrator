/*!
    \file    gd32f30x_it.c
    \brief   interrupt service routines

    \version 2017-02-10, V1.0.0, firmware for GD32F30x
    \version 2018-10-10, V1.1.0, firmware for GD32F30x
    \version 2018-12-25, V2.0.0, firmware for GD32F30x
    \version 2020-09-30, V2.1.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32f30x_it.h"


/*
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while (1){
    }
}

/*!
    \brief      this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1){
    }
}

/*!
    \brief      this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1){
    }
}

/*!
    \brief      this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1){
    }
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
}

/*!
    \brief      this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
}

/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
    delay_decrement();
}


/*!
    \brief      this function handles USART RBNE interrupt request and TBE interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/

unsigned int  t1_cnt1;
unsigned int  t1_cnt2;
unsigned int  t1_cnt3;

/*!
    \brief      this function handles TIMER1
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER1_IRQHandler(void)
{
	/*----------------------LED----------------------------*/
	static uint8_t n1 = 0;
	if(SET == timer_interrupt_flag_get(TIMER1, TIMER_INT_FLAG_UP))
	{
			/* 清除通道TIMER1中断位 */
			timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);
		
			if(n1 < 50)   //延时500ms
				n1++;
			else
			{
				n1 = 0;
			if(SET == gpio_output_bit_get(GPIOC,GPIO_PIN_1))
				LED(0);
			else
				LED(1);	
			}
		}	

   /*----------串口0超时----氧传感器------------------*/
			if(UART0_timeover <99)
			  UART0_timeover++;
			else
			{
				UART0_timeover = 0;
				
				UART0_Rxcount   = 0;
				UART0_RxSuccess = 0;

				O2_concent      = 0;
			}		
				
	/*-----------------------Valve-------------------------------*/
		if(bit_Valve)
		{
			/*判断是加压还是均压*/
			if(Valswith == 0)
			{
				Valswith_time	= Valve_COM * 10;
			}
			else
			{
				Valswith_time	=	Valve_Change	*10;
			}
			
			/*延时*/
			if(Valvetime1 < Valswith_time)
				Valvetime1++;
			else
			{
				Valvetime1 = 0;
				if(Valswith)
					Valswith = 0;
				else
					Valswith = 1;
				
				/*选择电磁阀是那种模式*/
				switch(Valve_step)
				{
					case 0:	Valve_step = 1;
							Valve1(1);
							Valve2(0);
							break;
					
					case 1:	Valve_step = 2;
							Valve1(1);
							Valve2(1);
							break;
					
					case 2:	Valve_step = 3;
							Valve1(0);
							Valve2(1);
							break;					
					
					case 3:Valve_step = 0;
							Valve1(1);
							Valve2(1);
							break;
					
					default:
							break;
				}
			}
			 Valvetime2 = 100;
		}
		else
		{
			if(Valvetime2 > 0)
			{
				Valvetime2--;
				Valve1(1);
				Valve2(1);
			}
			else
			{
				Valve1(0);
				Valve2(0);
			}
			
			Valswith 	= 0;
			Valvetime1 	= 0;
			Valve_step 	= 0;
			Valswith_time = 0;
		}
}

/*!
    \brief      this function handles TIMER5
    \param[in]  none
    \param[out] none
    \retval     none
*/
uint16_t timer5_1ms=0;

void TIMER5_IRQHandler(void)
{
	timer5_1ms = 1;
	if(SET == timer_interrupt_flag_get(TIMER5, TIMER_INT_FLAG_UP))
	{
			/* 清除通道TIMER1中断位 */
			timer_interrupt_flag_clear(TIMER5, TIMER_INT_FLAG_UP);
	}
}

