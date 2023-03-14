#include "DriValve.h"

void Dri_Valve_Init(void)
{
	/*打开GPIOA,GPIOB,GPIOC外设时钟*/
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	
	//打开复用外设时钟
	rcu_periph_clock_enable(RCU_AF);
		
//	使用SW下载,不使用JTAG下载,管脚用作其它功能 
//	gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);
	//初始化PB1，PB2引脚
	gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_1 | GPIO_PIN_2);	
}

/*timer1定时器初始化*/
void Timer1_Init(void)
{
    timer_parameter_struct timer_initpara;			//定义时基单元初始化结构体

    rcu_periph_clock_enable(RCU_TIMER1);				//使能更新事件中断

	//复位TIMER1
    timer_deinit(TIMER1);
	
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
	
    /* TIMER1 configuration */
    timer_initpara.prescaler         = 12000-1;						//设置预分频系数，
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;//CNT计数对齐模式
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;	//CNT寄存器计数方向
    timer_initpara.period            = 100-1;         		//设置自动重载寄存器，10ms
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;	/* DTS时间分频值*/
    timer_init(TIMER1, &timer_initpara);

    timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);//清除timer中断标志位
    timer_interrupt_enable(TIMER1, TIMER_INT_UP);					//timer1中断使能
    timer_enable(TIMER1);																	//使能timer1
		
	nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
    nvic_irq_enable(TIMER1_IRQn, 1, 1);										/* Timer5中断设置，抢占优先级0，子优先级0 */
}

/*timer1定时器初始化*/
void Timer5_Init(void)
{
    timer_parameter_struct timer_initpara;			//定义时基单元初始化结构体

    rcu_periph_clock_enable(RCU_TIMER5);				//使能更新事件中断

	/*复位TIMER13*/
    timer_deinit(TIMER5);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER1 configuration */
	
    timer_initpara.prescaler         = 12000-1;					//设置预分频系数，
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;		//CNT计数对齐模式
//  timer_initpara.counterdirection  = TIMER_COUNTER_UP;		//CNT寄存器计数方向
    timer_initpara.period            = 10-1;         			//设置自动重载寄存器，1ms
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;		/* DTS时间分频值*/
    timer_init(TIMER5, &timer_initpara);

    timer_interrupt_flag_clear(TIMER5, TIMER_INT_FLAG_UP);		//清除timer中断标志位
    timer_interrupt_enable(TIMER5, TIMER_INT_UP);				//timer1中断使能
    timer_enable(TIMER5);																	//使能timer1
		
	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
    nvic_irq_enable(TIMER5_IRQn, 0, 0);							/* Timer5中断设置，抢占优先级0，子优先级0 */
}

void Dri_Valve(void)
{
	Dri_Valve_Init();
	Timer1_Init();
	Timer5_Init();
}
