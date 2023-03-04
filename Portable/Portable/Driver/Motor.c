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

#define MOTOR_ADDR   0XA4  //�����������ַ

#define MOTOR_SDA(x)   ((x) ? (gpio_bit_set(GPIOA,GPIO_PIN_6)) : (gpio_bit_reset(GPIOA,GPIO_PIN_6)))
#define MOTOR_SCL(x)   ((x) ? (gpio_bit_set(GPIOC,GPIO_PIN_4)) : (gpio_bit_reset(GPIOC,GPIO_PIN_4)))

#define MOTOR_SDA_Read   gpio_input_bit_get(GPIOA,GPIO_PIN_6)

#define MOTOR_SDA_IN   gpio_init(GPIOA,GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_6)  //����Ϊ����
#define MOTOR_SDA_OUT  gpio_init(GPIOA,GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6)  //����Ϊ���


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
* ��    �ƣ�uint8_t IIC_Wait_Ack(void)
* ��    �ܣ��ȴ�ACKӦ��
* ��ڲ�������
* ���ڲ�����������ֵ=Ӧ�𣬷��ؼ�ֵ=��Ӧ��
* ˵    �����յ�Ӧ���źź�Ҫ��50US������ʱ��������һ�����ݲ�����
* ���÷������� 
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
	delays(200); //�˴�Ҫ�ӳ���ʱ 80
	
	return TRUE;
}
/****************************************************************************
* ��    �ƣ�void IIC_Ack(uint8_t Ack)
* ��    �ܣ�IIC ACKӦ��
* ��ڲ����� Ack �����л�Ӧ��ͷ�Ӧ��
* ���ڲ�������
* ˵    ����Ack=1 Ӧ��Ack=0 ��Ӧ��
* ���÷������� 
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
	delays(200);    //�˴�Ҫ�ӳ���ʱ 80
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
			ReceiveByte<<=1;//���ݴӸ�λ����λ//
			MOTOR_SCL_H;
			delays(20);
      if(MOTOR_SDA_Read)  
				ReceiveByte|=0x01;
			MOTOR_SCL_L;
			delays(20);
    }
		if(Ack)  
			MOTOR_IIC_Ack(1);//�������ݺ�Ҫ����Ӧ����߷�Ӧ���ź�
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

//#define MOTOR_ADDR   0XA4  //�����������ַ

//unsigned char motor_send[8];


///* ������us����ʱ����
// * ����nus����Ҫ��ʱ��us��
// * ����ֵ����*/		    								   
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

///* ����������I2C����,������I2C��ʼ����. 
// * ������  ��
// * ����ֵ����						*/
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

///* ����������I2C����,������I2C��������.  
// * ������  ��
// * ����ֵ����						*/
//void Motor_IIC_Stop(void)
//{
//	SDA_OUT();
//	IIC_SCL(1);
//	delay_us(4);
//	IIC_SDA(0);
//	delay_us(4);
//	IIC_SDA(1);
//}

///* ������IIC ACKӦ��
// * ������ACK  �����л�Ӧ��ͷ�Ӧ��
// * ˵����Ack=1 Ӧ��Ack=0 ��Ӧ��
// * ����ֵ����		*/
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


///* �������ȴ�ACK 
// * ������  ��
// * ����ֵ���ȴ�Ӧ�𷵻�0��û�еȴ���Ӧ�𷵻�1*/
//uint8_t	Motor_IIC_Wait_ACK(void)
//{
//	 uint8_t t = 200;
//    SDA_OUT();
//    IIC_SDA(1);		
//    delay_us(1);
//    IIC_SCL(0);
//    delay_us(1); 
//    SDA_IN();		/* ���ݷ�������ͷ������ߣ�׼������Ӧ��λ */
//    delay_us(1); 
//    while(READ_SDA)	/* �ȴ�IICӦ��*/
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

///* ������һ���ֽ����ݷ��ͺ���               
// * ������  ��
// * ����ֵ����		*/
//void Motor_IIC_SendByte(uint8_t byte)
//{
//	uint8_t BitCnt;
//	SDA_OUT();
//	IIC_SCL(0);
//	for(BitCnt=0;BitCnt<8;BitCnt++) /* Ҫ���͵����ݳ���Ϊ8λ */
//	{
//		if(byte&0x80) IIC_SDA(1);	/* �жϷ���λ */
//		else IIC_SDA(0); 
//		byte<<=1;
//		delay_us(2); 
//		IIC_SCL(1);
//		delay_us(2);
//		IIC_SCL(0);
//		delay_us(2);
//	}
//}

///* ������һ���ֽ����ݽ��պ���               
// * ������  ��
// * ����ֵ�����յ����ֽ�����		*/   
//uint8_t IIC_Read_Byte(uint8_t ACK)//��һ���ֽ�
//{ 
//	unsigned i,receive = 0;
//	
//	SDA_IN(); //SDA����Ϊ����
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
//		Motor_IIC_ACK(1);//�������ݺ�Ҫ����Ӧ����߷�Ӧ���ź�
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


