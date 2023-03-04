#include "DriMotor.h"

#define FALSE 0
#define TRUE  1

void Dri_Motor_IIC_Init()
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOC);
	gpio_init(GPIOA,GPIO_MODE_AIN,GPIO_OSPEED_50MHZ,GPIO_PIN_6);
	gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_4);
	gpio_bit_set(GPIOB,GPIO_PIN_6);
	gpio_bit_set(GPIOC,GPIO_PIN_4);
}

#define MOTOR_ADDR   0XA4  //电机控制器地址

#define MOTOR_SDA(x)   ((x) ? (gpio_bit_set(GPIOA,GPIO_PIN_6)) : (gpio_bit_reset(GPIOA,GPIO_PIN_6)))
#define MOTOR_SCL(x)   ((x) ? (gpio_bit_set(GPIOC,GPIO_PIN_4)) : (gpio_bit_reset(GPIOC,GPIO_PIN_4)))

#define MOTOR_SDA_Read   gpio_input_bit_get(GPIOA,GPIO_PIN_6)

#define MOTOR_SDA_IN   gpio_init(GPIOA,GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_6)  //设置为输入
#define MOTOR_SDA_OUT  gpio_init(GPIOA,GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6)  //设置为输出


#define MOTOR_SDA_H  gpio_bit_set  (GPIOA,GPIO_PIN_6)
#define MOTOR_SDA_L  gpio_bit_reset(GPIOA,GPIO_PIN_6)


#define MOTOR_SCL_H  gpio_bit_set  (GPIOC,GPIO_PIN_4)
#define MOTOR_SCL_L  gpio_bit_reset(GPIOC,GPIO_PIN_4)


unsigned char motor_send[8];



void delays(unsigned int temp)
{
	 unsigned int i;
	
	
	 i = temp*20;
	 while(i)
	 {
		 i--;
	 }

}


//IIC Start
void Dri_MOTOR_IIC_Start(void)
{
	MOTOR_SDA_OUT;	
	delays(20);
	
	MOTOR_SDA_H;
	delays(20);
	MOTOR_SCL_H;
	delays(20);
	MOTOR_SDA_L;
}

//IIC Stop
void Dri_MOTOR_IIC_Stop(void)
{
	
	MOTOR_SDA_OUT;
	delays(20);
	
	MOTOR_SCL_H;
	MOTOR_SDA_L;
	delays(20);
	MOTOR_SDA_H;	

}
/****************************************************************************
* 名    称：uint8_t IIC_Wait_Ack(void)
* 功    能：等待ACK应答
* 入口参数：无
* 出口参数：返回真值=应答，返回假值=无应答
* 说    明：收到应答信号后要加50US以上延时，发送下一个数据才正常
* 调用方法：无 
****************************************************************************/
uint8_t Dri_MOTOR_IIC_Wait_Ack(void)
{
	uint16_t time = 0;
	
	MOTOR_SDA_OUT;
	MOTOR_SDA_H;
	delays(200);
	
	MOTOR_SDA_IN;
	delays(50);
	
	while(MOTOR_SDA_Read)
	{
		time++;
		if(time > 250)
		{
			Dri_MOTOR_IIC_Stop();
			return FALSE;
		}
	}
	MOTOR_SCL_H;
	delays(20);
	MOTOR_SCL_L;
	delays(200); //此处要加长延时 80
	
	return TRUE;
}
/****************************************************************************
* 名    称：void IIC_Ack(uint8_t Ack)
* 功    能：IIC ACK应答
* 入口参数： Ack 用于切换应答和非应答
* 出口参数：无
* 说    明：Ack=1 应答；Ack=0 非应答
* 调用方法：无 
****************************************************************************/
void Dri_MOTOR_IIC_Ack(uint8_t Ack)
{	

	
	MOTOR_SDA_OUT;
	delays(50);
	
	if(Ack)
		MOTOR_SDA_L;
	else 
		MOTOR_SDA_H;
	MOTOR_SCL_H;
	delays(20);
	MOTOR_SCL_L;
	delays(200);    //此处要加长延时 80
}

// IIC Write byte
void Dri_MOTOR_Write_IIC_Byte(uint8_t IIC_Byte)
{
	uint8_t i;
	
	delays(10);
	MOTOR_SCL_L;
	MOTOR_SDA_OUT;
	delays(50);
	
	for(i=0;i<8;i++)
	{ 	
		if(IIC_Byte&0x80)
			MOTOR_SDA_H;  
		else 
			MOTOR_SDA_L;
		
		IIC_Byte<<=1;
		delays(20);
		
		MOTOR_SCL_H; 
		delays(20);
		MOTOR_SCL_L;
		delays(20);		
	}
	MOTOR_SDA_L;
	MOTOR_SCL_L;
}

// Read_IIC_Byte
uint8_t Dri_MOTOR_Read_IIC_Byte(uint8_t Ack)  
{ 
    uint8_t i,ReceiveByte=0;
  
		MOTOR_SDA_IN;	
	  delays(20);
	
    for(i=0;i<8;i++)
    {		
			ReceiveByte<<=1;//数据从高位到低位//
			MOTOR_SCL_H;
			delays(20);
      if(MOTOR_SDA_Read)  
				ReceiveByte|=0x01;
			MOTOR_SCL_L;
			delays(20);
    }
		if(Ack)  
			Dri_MOTOR_IIC_Ack(1);//读完数据后要发送应答或者非应答信号
		else 
			Dri_MOTOR_IIC_Ack(0);
    return ReceiveByte;
}


void  Dri_Motor(void)
{
	  unsigned char i;
	

	  Dri_MOTOR_IIC_Start();

	  Dri_MOTOR_Write_IIC_Byte(MOTOR_ADDR);	
	 
	  Dri_MOTOR_IIC_Wait_Ack();
	  
	  for(i=0;i<8;i++)
	  {
		  Dri_MOTOR_Read_IIC_Byte(motor_send[i]);
		  Dri_MOTOR_IIC_Wait_Ack();
	  }
	 
	 Dri_MOTOR_IIC_Stop();
	
}