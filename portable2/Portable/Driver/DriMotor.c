#include "DriMotor.h"

/*���õ��ת�ٵ�����*/
unsigned char motor_send[8];

/*
* ��    �ƣ�delays()
* ��    �ܣ�΢����ʱ����
* ��ڲ�����temp
* ���ڲ�������
* ˵    ������
* ���÷������� 
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
* ��    �ƣ�Dri_Motor_IIC_Init()
* ��    �ܣ����ų�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
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
* ��    �ƣ�Dri_MOTOR_IIC_Start()
* ��    �ܣ�IIC�Ŀ�ʼ�ź�
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
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
* ��    �ƣ�Dri_MOTOR_IIC_Stop()
* ��    �ܣ�IIC ֹͣ�ź�
* ��ڲ����� ��
* ���ڲ�������
* ˵    ������
* ���÷������� 
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
* ��    �ƣ�uint8_t IIC_Wait_Ack(void)
* ��    �ܣ��ȴ�ACKӦ��
* ��ڲ�������
* ���ڲ�����������ֵ=Ӧ�𣬷��ؼ�ֵ=��Ӧ��
* ˵    �����յ�Ӧ���źź�Ҫ��50US������ʱ��������һ�����ݲ�����
* ���÷������� 
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
	delays(200); //�˴�Ҫ�ӳ���ʱ 80
	
	return TRUE;
}

/*
* ��    �ƣ�void IIC_Ack(uint8_t Ack)
* ��    �ܣ�IIC ACKӦ��
* ��ڲ����� Ack �����л�Ӧ��ͷ�Ӧ��
* ���ڲ�������
* ˵    ����Ack=1 Ӧ��Ack=0 ��Ӧ��
* ���÷������� 
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
	delays(200);    //�˴�Ҫ�ӳ���ʱ 80
}

/*
* ��    �ƣ�Dri_MOTOR_Write_IIC_Byte����
* ��    �ܣ�д��һ���ֽ�
* ��ڲ����� IIC_Byte
* ���ڲ�������
* ˵    ������
* ���÷������� 
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
* ��    �ƣ�Dri_MOTOR_Read_IIC_Byte(uint8_t Ack) 
* ��    �ܣ����յ�һ���ֽ�
* ��ڲ�����Ack		�Ƿ�Ӧ��
* ���ڲ�����ReceiveByte
* ˵    ������
* ���÷������� 
*/
uint8_t Dri_MOTOR_Read_IIC_Byte(uint8_t Ack)  
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
	  {
		ReceiveByte|=0x01;
	  }		  
			
		MOTOR_SCL_L;
		delays(20);
    }
		if(Ack)  
			Dri_MOTOR_IIC_Ack(1);//�������ݺ�Ҫ����Ӧ����߷�Ӧ���ź�
		else 
			Dri_MOTOR_IIC_Ack(0);
    return ReceiveByte;
}

/*
* ��    �ƣ�Dri_Motor(void)
* ��    �ܣ�IIC����ʱ��
* ��ڲ�������
* ���ڲ�������
* ˵    ������
* ���÷������� 
*/
void  Dri_Motor(void)
{
	  unsigned char i;
	
	  Dri_MOTOR_IIC_Start();					//��ʼ�ź�

	  Dri_MOTOR_Write_IIC_Byte(MOTOR_ADDR);		//д��һ���ֽ�
	 
	  Dri_MOTOR_IIC_Wait_Ack();					//�ȴ�Ӧ���ź�
	  
	  for(i=0;i<8;i++)
	  {
		  Dri_MOTOR_Read_IIC_Byte(motor_send[i]);	//���ֽ�
		  Dri_MOTOR_IIC_Wait_Ack();					
	  }
	 
	 Dri_MOTOR_IIC_Stop();						//ֹͣ�ź�
	
}