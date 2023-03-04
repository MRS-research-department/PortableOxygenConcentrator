#include "main.h"

unsigned char	bit_EMC_Started;
unsigned char 	bit_Valve;				//判断电磁阀是否开启  1开启   0关闭
unsigned int	Valswith = 0;			//判断是均压还是加压  0是共同时间   1是单个时间
unsigned int 	Valswith_time;
unsigned int	Valve_COM 	= 4;		//均压时间
unsigned int	Valve_Change = 40;		//加压时间
unsigned int	Valvetime1;				//延迟时间	
unsigned char 	Valve_step;
unsigned int 	Valvetime2;				//关闭电磁阀延时

unsigned char 	bit_RUN = 0;

extern uint16_t timer5_1ms;

int main(void)
{
		systick_config();	//配置时钟使能
		LED_Init();
		LCD_Init();
	
		Key_GPIO_Init();
		Motor_IIC_Init();
		Valve_Init();

	    uint8_t a=0;
	

		while(1)
		{
			Motor();

			uint8_t n=Key4();
			if(n == RESET)
			{
				static uint8_t key_up = 1;
				if(key_up && n==RESET)
				{
					key_up=0;
					if(n == RESET)
					{
						LCD_ShowString(5, 10, 12, 12, 12, "1");						
						bit_Valve = 1;
						motor_send[0] = 60;	
						while((a<50)&&(n==1))
						{
					      a++;	
						}
					}
				}
				else 
				{
					LCD_ShowString(5, 10, 12, 12, 12, "0"); 
					motor_send[0] = 0;
					bit_Valve = 0;	
				    key_up=1;
				 }

				}
		}
			
	}	
//			LCD_ShowString(5, 10, 12, 12, 12, "0"); 
//			motor_send[0] = 0;
//			for(b=0;b>200;b++) ;
//			bit_Valve = 0;	

//			LCD_ShowString(5, 10, 12, 12, 12, "1");						
//			bit_Valve = 1;
//			for(b=0;b>200;b++) ;
//			motor_send[0] = 60;	
			
//			uint8_t str[] = "HELLO!\r\n";
//			uint32_t len = sizeof(str)/sizeof(*str);
//			uart_data_transmit(str,len-1);

	
	
/*Define the parameters used in the program.*/
//typedef struct 
//{
//	uint32_t single_time;										/*Accumulate time in one time*/
//	uint32_t accumulate_time;								/*Accumulate time in total*/
//	uint32_t real_accumulate_time;						/*Accumulate time in the real time*/
//	uint32_t accumulate_display_time;				/*Accumulate time to display*/
//	uint32_t mem_accumulate_time;						/*Accumulate time in memory*/	
// 	uint16_t set_time;												/*Set Time*/
//	uint16_t time_1s_count;									/*Basic Time*/
//	
//	uint16_t LCD_brightness;									/*The brightness of LCD*/
//		

//	uint16_t FAN_Speed;											/*The speed of FAN*/		
//	
//	uint16_t BLDC_Speed;											/*The speed of BLDC*/	

//	uint8_t alarm_message;										/*Alarm messages*/

//	uint8_t density;													/*System density*/
//	uint8_t respiratory_rate;								/*System respiratory rate*/
//	uint8_t mode;														/*System mode*/
//	uint8_t mode_last;												/*System last mode*/
//	uint8_t grade;														/*System grade*/

//	FlagStatus vavle_start_up_flag;			/*System vavle_start_up_flag*/
//	FlagStatus keys_ack;								/*The acknowledge of key1 and key2 are triggered together.*/
//	
//}System_ParaTypeDef;

//extern System_ParaTypeDef system;