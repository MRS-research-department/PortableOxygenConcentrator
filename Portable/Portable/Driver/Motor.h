#ifndef MOTOR_H
#define MOTOR_H

#include "gd32f30x.h"
#include "systick.h"

/*SM BUS IO ASSIGNMENTS*/
#define SDA_IN()  		gpio_init(GPIOA,GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_6 )		
#define SDA_OUT() 		gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6 )	

#define IIC_SDA(n)		(n?(gpio_bit_set(GPIOA,GPIO_PIN_6)):(gpio_bit_reset(GPIOA,GPIO_PIN_6)))
#define	IIC_SCL(n)		(n?(gpio_bit_set(GPIOC,GPIO_PIN_4)):(gpio_bit_reset(GPIOC,GPIO_PIN_4)))

#define READ_SDA   		gpio_input_bit_get(GPIOA,GPIO_PIN_6)

extern unsigned char motor_send[8];

//void delays(uint32_t nus);
//void Motor_IIC_Init(void);
//void Motor_IIC_Start(void);
//void Motor_IIC_Stop(void);
//void Motor_IIC_ACK(uint8_t ACK);
//unsigned char	Motor_IIC_Wait_ACK(void);
//void Motor_IIC_SendByte(uint8_t byte);
//uint8_t IIC_Read_Byte(uint8_t ACK);
//void Motor(void);

void Motor_IIC_Init(void);
void MOTOR_IIC_Start(void);
void MOTOR_IIC_Stop(void);
uint8_t MOTOR_IIC_Wait_Ack(void);
void MOTOR_IIC_Ack(uint8_t Ack);		
void MOTOR_Write_IIC_Byte(uint8_t IIC_Byte);	
uint8_t MOTOR_Read_IIC_Byte(uint8_t Ack);	
void  Motor(void);	
#endif

