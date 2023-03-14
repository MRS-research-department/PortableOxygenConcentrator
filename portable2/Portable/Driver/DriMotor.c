#include "DriMotor.h"

/*设置电机转速的数组*/
unsigned char motor_send[8];

/*
* 名    称：delays()
* 功    能：微秒延时函数
* 入口参数：temp
* 出口参数：无
* 说    明：无
* 调用方法：无 
*/
void delays(unsigned int temp)
{
	 unsigned int i;
	
	 i = temp*20;
	 while(i)
	 {
		 i--;
	 }
}


/*
* 名    称：Dri_Motor_IIC_Init()
* 功    能：引脚初始化
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
*/
void Dri_Motor_IIC_Init()
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOC);
	gpio_init(GPIOA,GPIO_MODE_AIN,GPIO_OSPEED_50MHZ,GPIO_PIN_6);
	gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_4);
	gpio_bit_set(GPIOB,GPIO_PIN_6);
	gpio_bit_set(GPIOC,GPIO_PIN_4);
}

/*
* 名    称：Dri_MOTOR_IIC_Start()
* 功    能：IIC的开始信号
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
*/
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

/*
* 名    称：Dri_MOTOR_IIC_Stop()
* 功    能：IIC 停止信号
* 入口参数： 无
* 出口参数：无
* 说    明：无
* 调用方法：无 
*/
void Dri_MOTOR_IIC_Stop(void)
{	
	MOTOR_SDA_OUT;
	delays(20);
	
	MOTOR_SCL_H;
	MOTOR_SDA_L;
	delays(20);
	MOTOR_SDA_H;	
}

/*
* 名    称：uint8_t IIC_Wait_Ack(void)
* 功    能：等待ACK应答
* 入口参数：无
* 出口参数：返回真值=应答，返回假值=无应答
* 说    明：收到应答信号后要加50US以上延时，发送下一个数据才正常
* 调用方法：无 
*/
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

/*
* 名    称：void IIC_Ack(uint8_t Ack)
* 功    能：IIC ACK应答
* 入口参数： Ack 用于切换应答和非应答
* 出口参数：无
* 说    明：Ack=1 应答；Ack=0 非应答
* 调用方法：无 
*/
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

/*
* 名    称：Dri_MOTOR_Write_IIC_Byte（）
* 功    能：写入一个字节
* 入口参数： IIC_Byte
* 出口参数：无
* 说    明：无
* 调用方法：无 
*/
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

/*
* 名    称：Dri_MOTOR_Read_IIC_Byte(uint8_t Ack) 
* 功    能：接收到一个字节
* 入口参数：Ack		是否应答
* 出口参数：ReceiveByte
* 说    明：无
* 调用方法：无 
*/
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
	  {
		ReceiveByte|=0x01;
	  }		  
			
		MOTOR_SCL_L;
		delays(20);
    }
		if(Ack)  
			Dri_MOTOR_IIC_Ack(1);//读完数据后要发送应答或者非应答信号
		else 
			Dri_MOTOR_IIC_Ack(0);
    return ReceiveByte;
}

/*
* 名    称：Dri_Motor(void)
* 功    能：IIC完整时序
* 入口参数：无
* 出口参数：无
* 说    明：无
* 调用方法：无 
*/
void  Dri_Motor(void)
{
	  unsigned char i;
	
	  Dri_MOTOR_IIC_Start();					//开始信号

	  Dri_MOTOR_Write_IIC_Byte(MOTOR_ADDR);		//写入一个字节
	 
	  Dri_MOTOR_IIC_Wait_Ack();					//等待应答信号
	  
	  for(i=0;i<8;i++)
	  {
		  Dri_MOTOR_Read_IIC_Byte(motor_send[i]);	//读字节
		  Dri_MOTOR_IIC_Wait_Ack();					
	  }
	 
	 Dri_MOTOR_IIC_Stop();						//停止信号
	
}