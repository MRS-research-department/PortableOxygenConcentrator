#include "DriValve.h"

void Dri_Valve_Init(void)
{
	/*��GPIOA,GPIOB,GPIOC����ʱ��*/
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	
	//�򿪸�������ʱ��
	rcu_periph_clock_enable(RCU_AF);
		
//	ʹ��SW����,��ʹ��JTAG����,�ܽ������������� 
//	gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);
	//��ʼ��PB1��PB2����
	gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_1 | GPIO_PIN_2);	
}

/*timer1��ʱ����ʼ��*/
void Timer1_Init(void)
{
    timer_parameter_struct timer_initpara;			//����ʱ����Ԫ��ʼ���ṹ��

    rcu_periph_clock_enable(RCU_TIMER1);				//ʹ�ܸ����¼��ж�

	//��λTIMER1
    timer_deinit(TIMER1);
	
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
	
    /* TIMER1 configuration */
    timer_initpara.prescaler         = 12000-1;						//����Ԥ��Ƶϵ����
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;//CNT��������ģʽ
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;	//CNT�Ĵ�����������
    timer_initpara.period            = 100-1;         		//�����Զ����ؼĴ�����10ms
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;	/* DTSʱ���Ƶֵ*/
    timer_init(TIMER1, &timer_initpara);

    timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);//���timer�жϱ�־λ
    timer_interrupt_enable(TIMER1, TIMER_INT_UP);					//timer1�ж�ʹ��
    timer_enable(TIMER1);																	//ʹ��timer1
		
	nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
    nvic_irq_enable(TIMER1_IRQn, 1, 1);										/* Timer5�ж����ã���ռ���ȼ�0�������ȼ�0 */
}

/*timer1��ʱ����ʼ��*/
void Timer5_Init(void)
{
    timer_parameter_struct timer_initpara;			//����ʱ����Ԫ��ʼ���ṹ��

    rcu_periph_clock_enable(RCU_TIMER5);				//ʹ�ܸ����¼��ж�

	/*��λTIMER13*/
    timer_deinit(TIMER5);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER1 configuration */
	
    timer_initpara.prescaler         = 12000-1;					//����Ԥ��Ƶϵ����
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;		//CNT��������ģʽ
//  timer_initpara.counterdirection  = TIMER_COUNTER_UP;		//CNT�Ĵ�����������
    timer_initpara.period            = 10-1;         			//�����Զ����ؼĴ�����1ms
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;		/* DTSʱ���Ƶֵ*/
    timer_init(TIMER5, &timer_initpara);

    timer_interrupt_flag_clear(TIMER5, TIMER_INT_FLAG_UP);		//���timer�жϱ�־λ
    timer_interrupt_enable(TIMER5, TIMER_INT_UP);				//timer1�ж�ʹ��
    timer_enable(TIMER5);																	//ʹ��timer1
		
	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
    nvic_irq_enable(TIMER5_IRQn, 0, 0);							/* Timer5�ж����ã���ռ���ȼ�0�������ȼ�0 */
}

void Dri_Valve(void)
{
	Dri_Valve_Init();
	Timer1_Init();
	Timer5_Init();
}
