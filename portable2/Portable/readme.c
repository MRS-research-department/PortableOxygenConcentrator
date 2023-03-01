/**
  ******************************************************************************
  * @file    readme.c
  * @author  Medris R&D
  * @version V1.0.0
  * @date    1-March-2023
  * @brief   This file provides the rules of the code. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2023 Medris R&D
  ******************************************************************************
  */



/**
  *文件名
	*文件名内包含的每个单词的首个字母用大写字母，其余使用小写字母。
	*文件名要使用能表达其功能的单词。
	*如果名称是由数个单词组成，那么词与词之间最好用下划线来隔开。
	*如果单词有缩写的，要保留能够识别其含义的关键字母。
	*
	*变量名
	*变量名全部用小写字母。
	*变量名要使用能表达其功能的单词。
	*如果名称是由数个单词组成，那么词与词之间用下划线来隔开。
	*在下述分类的变量名中首字母要小写。
	*
	*函数名
	*函数名要以用表示主动的动词为基本，没什么问题的话在其后面加上名词。
	*一般以大写字母开头。
	*由多个单词组成的名称，其单词与单词之间的区分要通过大写单词首字母来实现。
	*使用的动词，名词能表达函数实际的操作和功能。
	*不使用如a，b，c等没有意义的名词。
	*
	*常量名
	*被#define的常量名全部用大写。
	*在enum中声明的枚举型常量全部用大写。
	*由多个单词组成的名称，单词与单词之间用下划线来划分。
  */
	
	
	/**	
	*文件前头描述以下注视内容
	*項目	   	格式/内容
	*文件名		【格式】	@file	文件名
	*			【内容】 	记载文件名
	*			            ※文件名如果不被记入到注释里就不能在文件里显示。
	*
	*摘要说明	【格式 】 @brief 摘要说明
	*			【内容】  表示文件内容的名词
	*			  		  ※○○功能的文件 etc.
  */
	


/*=====================================================================================================================*/
	
	
	
/**	
	*函数前头记述以下注释内容
	*項目名	格式/内容
	*摘要说明	【格式】 @brief  摘要说明
	*					【内容】表示函数功能的名词
	*　				 ※  比如oo功能函数等 。
	*
	*输入参数	【格式】 @param [in] 参数名  说明
	*					【内容】  输入参数和说明
	*
	*输出参数	【格式】 @param [out]参数名 説明
	*					【内容】  输出参数和说明
	*
	*输入输出	【格式】 @param [in,out] 参数名 说明
	*					【内容】  输入输出参数和说明
	*
	*返回值		【格式】 @return返回值的说明
	*					【内容】	void函数，没有的情况写“没有或者无”
	*
  */
	
	
/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param [in]  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param [in] ADC_IT: specifies the ADC interrupt sources to be enabled or disabled. 
  *   This parameter can be any combination of the following values:
  *     @arg ADC_IT_EOC: End of conversion interrupt mask
  *     @arg ADC_IT_AWD: Analog watchdog interrupt mask
  *     @arg ADC_IT_JEOC: End of injected conversion interrupt mask
  * @param [in] NewState: new state of the specified ADC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @param [out] None
  * @param [in,out] None
  * @retval None
  */
//void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState)
//{
//  uint8_t itmask = 0;
//  /* Check the parameters */
//  assert_param(IS_ADC_ALL_PERIPH(ADCx));
//  assert_param(IS_FUNCTIONAL_STATE(NewState));
//  assert_param(IS_ADC_IT(ADC_IT));
//  /* Get the ADC IT index */
//  itmask = (uint8_t)ADC_IT;
//  if (NewState != DISABLE)
//  {
//    /* Enable the selected ADC interrupts */
//    ADCx->CR1 |= itmask;
//  }
//  else
//  {
//    /* Disable the selected ADC interrupts */
//    ADCx->CR1 &= (~(uint32_t)itmask);
//  }
//}
	
/*=====================================================================================================================*/
	
	
/**		
*规定有关大括弧({ })和缩进，空白的填写格式
*大括弧 （｛ ｝）的位置
*统一函数定义，控制结构（for，if-else，while等），结构体等中使用的｛｝的书写方法。代表性的描述方法参考下面事例。
*控制结构（for，if-else，while等）中，只要对原文件容量没有限制，运行步骤即便是仅一行也不省略｛｝。（因为追加运行步骤时，有可能出现问题）

*〔注释〕
*(1) 定义函数的时候，开始／終了｛｝描述应在同一列。
*	函数名（参数）
*	{ 
*		描述处理
*		…;
*	}
*	
*(2) 其他控制结构（for，if-else，while等）和结构体中，表示开始的｛的描述应在开始行末端。（注释除外）
*	if（…）{
*	  …;
*	｝
*	else if(…){
*		 …;
*		 ｝
*		 else{
*		 …;
*		 ｝
*
* 缩进
*(3) 缩进基准为4个字符宽度的TAB。
* 
* 添加空格的方法
*(4) 双目运算符以及3目运算符的前后要添加空格。但是，以下运算符除外。
*
*[ ]、 ->、 .( 句号)、 ,( 逗号运算符)
*(5) 单目运算符和运算项之间不空格添加空格。
*/				
				
/*=====================================================================================================================*/			
	
/*中断分配
中断名	优先级	用途
UART5 	12 			BLE
UART3 	15			浓度传感器

TIMER3 	3				提供10ms和100ms时基
TIMER4 	4				电机反馈，外部中断
TIMER5 	5				制氧阀控制
TIMER6 	6				时间累积
TIMER7 	7				ADC采集
TIMER8 	8				备用

*/


/*屏取模方式
逆向
列行式
C51

*/

/******************* (C) COPYRIGHT 2023 Medris R&D *****END OF FILE****/
	