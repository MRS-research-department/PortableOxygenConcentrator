#include "main.h"
#include "stdio.h"
unsigned char	bit_EMC_Started;
unsigned char 	bit_Valve;				//ï¿½Ð¶Ïµï¿½Å·ï¿½ï¿½Ç·ï¿½ï¿½ï¿??  1ï¿½ï¿½ï¿½ï¿½   0ï¿½Ø±ï¿½
unsigned int	Valswith = 0;			//ï¿½Ð¶ï¿½ï¿½Ç¾ï¿½Ñ¹ï¿½ï¿½ï¿½Ç¼ï¿½Ñ¹  0ï¿½Ç¹ï¿½Í¬Ê±ï¿½ï¿½   1ï¿½Çµï¿½ï¿½ï¿½Ê±ï¿½ï¿½
unsigned int 	Valswith_time;
unsigned int	Valve_COM 	= 4;		//ï¿½ï¿½Ñ¹Ê±ï¿½ï¿½
unsigned int	Valve_Change = 40;		//ï¿½ï¿½Ñ¹Ê±ï¿½ï¿½
unsigned int	Valvetime1;				//ï¿½Ó³ï¿½Ê±ï¿½ï¿½	
unsigned char 	Valve_step;
unsigned int 	Valvetime2;				//ï¿½Ø±Õµï¿½Å·ï¿½ï¿½ï¿½ï¿½?


unsigned char back_O2_gear = 0;     //ÑõÆøµç´Å·§µµÎ»,
unsigned char back_O2_mode = 0;     //ÖÆÑõ»ú¹¤×÷Ä£Ê½

unsigned char 	bit_RUN = 0;

extern uint16_t timer5_1ms;

int main(void)
{
//		static uint8_t Key4_Pressed = RESET;	   //µ±Ç°°´¼ü×´Ì¬
//		static uint8_t Key4_Last_Pressed  = RESET;	//ÉÏ´Î°´¼ü×´Ì¬
//		uint8_t Key4_Status = RESET;				
//		uint8_t Start_Up = RESET;

		systick_config();	//ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½Ê¹ï¿½ï¿½
		LED_Init();
		LCD_Init();
	
		Key_GPIO_Init();
		Motor_IIC_Init();
		Valve_Init();
		uart_config();
	
		printf("a usart transmit test example!");
		uint8_t test[3] = {'1', '2', '3'};
		UART_Write(test, 3);

		while(1)
		{			
			

			
//			Motor();

//			Key4_Status = Key4();      //½«°´¼üµÄ×´Ì¬¸³¸øKey4_Status

//			if(Key4_Status == SET){
//				Key4_Pressed = SET;

//				if((Key4_Last_Pressed  == RESET) && (Key4_Pressed == SET) )// °´¼ü°´ÏÂÒ»Ë²¼ä
//				{
//					Key4_Last_Pressed  = Key4_Pressed;
//					Start_Up ^= 0X01;
//				}			
//			}
//			else{
//				Key4_Last_Pressed = RESET;
//				Key4_Pressed = RESET;

//			}


//			if( Start_Up == 0X01){
//				LCD_ShowString(5, 10, 12, 12, 12, 1);						
//				bit_Valve = 1;
//				motor_send[0] = 60;	
//			}
//			else{
//				LCD_ShowString(5, 10, 12, 12, 12, 0); 
//				motor_send[0] = 0;
//				bit_Valve = 0;	
//			}
		}
	}			
			


	
	
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