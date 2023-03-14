#ifndef DIRMOTOR_H
#define DIRMOTOR_H

#include "gd32f30x.h"
#include "systick.h"

#define FALSE 0
#define TRUE  1

/*电机控制器地址*/
#define MOTOR_ADDR   0XA4  

/*获取PB6引脚状态*/
#define MOTOR_SDA_Read   gpio_input_bit_get(GPIOA,GPIO_PIN_6)

/*获取PB4，PB6高低电平，1为高电平，0为低电平*/
//#define MOTOR_SDA(x)   ((x) ? (gpio_bit_set(GPIOA,GPIO_PIN_6)) : (gpio_bit_reset(GPIOA,GPIO_PIN_6)))
//#define MOTOR_SCL(x)   ((x) ? (gpio_bit_set(GPIOC,GPIO_PIN_4)) : (gpio_bit_reset(GPIOC,GPIO_PIN_4)))

/*设置PB6输入，输出模式*/
#define MOTOR_SDA_IN   gpio_init(GPIOA,GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_6)  //设置为输入
#define MOTOR_SDA_OUT  gpio_init(GPIOA,GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6)  //设置为输出

/*设置PB6的高低电平*/
#define MOTOR_SDA_H  gpio_bit_set  (GPIOA,GPIO_PIN_6)
#define MOTOR_SDA_L  gpio_bit_reset(GPIOA,GPIO_PIN_6)

/*设置PB4的高低电平*/
#define MOTOR_SCL_H  gpio_bit_set  (GPIOC,GPIO_PIN_4)
#define MOTOR_SCL_L  gpio_bit_reset(GPIOC,GPIO_PIN_4)

extern unsigned char motor_send[8];

void Dri_Motor_IIC_Init(void);
void Dri_MOTOR_IIC_Start(void);
void Dri_MOTOR_IIC_Stop(void);
uint8_t Dri_MOTOR_IIC_Wait_Ack(void);
void Dri_MOTOR_IIC_Ack(uint8_t Ack);		
void Dri_MOTOR_Write_IIC_Byte(uint8_t IIC_Byte);	
uint8_t Dri_MOTOR_Read_IIC_Byte(uint8_t Ack);	
void  Dri_Motor(void);	
#endif

