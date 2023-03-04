#include "Motor.h"

#define FALSE 0
#define TRUE  1

void Motor_IIC_Init()
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
void MOTOR_IIC_Start(void)
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
void MOTOR_IIC_Stop(void)
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
uint8_t MOTOR_IIC_Wait_Ack(void)
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
			MOTOR_IIC_Stop();
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
void MOTOR_IIC_Ack(uint8_t Ack)
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
void MOTOR_Write_IIC_Byte(uint8_t IIC_Byte)
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
uint8_t MOTOR_Read_IIC_Byte(uint8_t Ack)  
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
			MOTOR_IIC_Ack(1);//读完数据后要发送应答或者非应答信号
		else 
			MOTOR_IIC_Ack(0);
    return ReceiveByte;
}


void  Motor(void)
{
	  unsigned char i;
	

	  MOTOR_IIC_Start();

	  MOTOR_Write_IIC_Byte(MOTOR_ADDR);	
	 
	  MOTOR_IIC_Wait_Ack();
	  
	  for(i=0;i<8;i++)
	  {
		  MOTOR_Write_IIC_Byte(motor_send[i]);
		  MOTOR_IIC_Wait_Ack();
	  }
	 
	 MOTOR_IIC_Stop();
	
}





//#include "Motor.h"

//#define MOTOR_ADDR   0XA4  //电机控制器地址

//unsigned char motor_send[8];


///* 描述：us级延时函数
// * 参数nus：需要延时的us数
// * 返回值：无*/		    								   
//void delay_us(unsigned int temp)
//{
//	 unsigned int i;
//	
//	
//	 i = temp*20;
//	 while(i)
//	 {
//		 i--;
//	 }

//}

//void Motor_IIC_Init()
//{
//	rcu_periph_clock_enable(RCU_GPIOA);
//	rcu_periph_clock_enable(RCU_GPIOC);
//	gpio_init(GPIOA,GPIO_MODE_AIN,GPIO_OSPEED_50MHZ,GPIO_PIN_6);
//	gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_4);
//	gpio_bit_set(GPIOB,GPIO_PIN_6);
//	gpio_bit_set(GPIOC,GPIO_PIN_4);
//}

///* 描述：启动I2C总线,即发送I2C起始条件. 
// * 参数：  无
// * 返回值：无						*/
//void Motor_IIC_Start(void)
//{
//	SDA_OUT();
//	IIC_SDA(1);
//	delay_us(1);
//	IIC_SCL(1);
//	delay_us(1);
//	IIC_SDA(0);
//	delay_us(1);
//	IIC_SCL(0);
//}

///* 描述：结束I2C总线,即发送I2C结束条件.  
// * 参数：  无
// * 返回值：无						*/
//void Motor_IIC_Stop(void)
//{
//	SDA_OUT();
//	IIC_SCL(1);
//	delay_us(4);
//	IIC_SDA(0);
//	delay_us(4);
//	IIC_SDA(1);
//}

///* 描述：IIC ACK应答
// * 参数：ACK  用于切换应答和非应答
// * 说明：Ack=1 应答；Ack=0 非应答
// * 返回值：无		*/
//void Motor_IIC_ACK(uint8_t ACK)
//{
//	SDA_OUT();
//	delay_us(2);
//	if(ACK)
//		IIC_SDA(0);
//	else
//		IIC_SDA(1);
//	delay_us(4);
//	IIC_SCL(1);
//	delay_us(2);
//	IIC_SCL(0);
//	delay_us(4);
//}


///* 描述：等待ACK 
// * 参数：  无
// * 返回值：等待应答返回0，没有等待到应答返回1*/
//uint8_t	Motor_IIC_Wait_ACK(void)
//{
//	 uint8_t t = 200;
//    SDA_OUT();
//    IIC_SDA(1);		
//    delay_us(1);
//    IIC_SCL(0);
//    delay_us(1); 
//    SDA_IN();		/* 数据发送完后释放数据线，准备接收应答位 */
//    delay_us(1); 
//    while(READ_SDA)	/* 等待IIC应答*/
//    {
//		t--;
//		delay_us(1); 
//		if(t==0)
//		{
//			Motor_IIC_Stop();
//			return 0;
//		}
//		delay_us(1); 
//    }
//    delay_us(1);      
//    IIC_SCL(1);
//    delay_us(1);
//    IIC_SCL(0);             
//    delay_us(1);    
//    return 1;	
//}

///* 描述：一个字节数据发送函数               
// * 参数：  无
// * 返回值：无		*/
//void Motor_IIC_SendByte(uint8_t byte)
//{
//	uint8_t BitCnt;
//	SDA_OUT();
//	IIC_SCL(0);
//	for(BitCnt=0;BitCnt<8;BitCnt++) /* 要传送的数据长度为8位 */
//	{
//		if(byte&0x80) IIC_SDA(1);	/* 判断发送位 */
//		else IIC_SDA(0); 
//		byte<<=1;
//		delay_us(2); 
//		IIC_SCL(1);
//		delay_us(2);
//		IIC_SCL(0);
//		delay_us(2);
//	}
//}

///* 描述：一个字节数据接收函数               
// * 参数：  无
// * 返回值：接收到的字节数据		*/   
//uint8_t IIC_Read_Byte(uint8_t ACK)//读一个字节
//{ 
//	unsigned i,receive = 0;
//	
//	SDA_IN(); //SDA定义为输入
//	for(i = 0;i < 8;i++ )
//	{  
//		delay_us(4);
//		IIC_SCL(1);
//		receive <<= 1;
//		if(READ_SDA)
//		{
//			receive |=0x01;
//		}
//		delay_us(4); 
//		IIC_SCL(1);
//	}
//		if(ACK)  
//		Motor_IIC_ACK(1);//读完数据后要发送应答或者非应答信号
//		else 
//		Motor_IIC_ACK(0);
//	return receive;
//} 

//void Motor(void)
//{
//	unsigned char i;

//	Motor_IIC_Start();
//	Motor_IIC_SendByte(MOTOR_ADDR);
//	Motor_IIC_Wait_ACK();
//	for( i=0;i<8;i++)
//	{
//		Motor_IIC_SendByte(motor_send[i]);
//		Motor_IIC_Wait_ACK();
//	}
//	Motor_IIC_Stop();
//}


