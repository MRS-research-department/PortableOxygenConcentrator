
//void Timer1_Init(void)
//{
//    timer_parameter_struct timer_initpara;

//    rcu_periph_clock_enable(RCU_TIMER1);

//    timer_deinit(TIMER1);
//    /* initialize TIMER init parameter struct */
//    timer_struct_para_init(&timer_initpara);
//    /* TIMER1 configuration */
//	
//    timer_initpara.prescaler         = 11999;
//    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
//    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
//    timer_initpara.period            = 99;        //10MS
//    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
//    timer_init(TIMER1, &timer_initpara);

//    timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);
//    timer_interrupt_enable(TIMER1, TIMER_INT_UP);
//    timer_enable(TIMER1);
//		
//		nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
//    nvic_irq_enable(TIMER1_IRQn, 1, 1);
//}


