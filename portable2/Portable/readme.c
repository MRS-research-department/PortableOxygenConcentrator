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
  *�ļ���
	*�ļ����ڰ�����ÿ�����ʵ��׸���ĸ�ô�д��ĸ������ʹ��Сд��ĸ��
	*�ļ���Ҫʹ���ܱ���书�ܵĵ��ʡ�
	*���������������������ɣ���ô�����֮��������»�����������
	*�����������д�ģ�Ҫ�����ܹ�ʶ���京��Ĺؼ���ĸ��
	*
	*������
	*������ȫ����Сд��ĸ��
	*������Ҫʹ���ܱ���书�ܵĵ��ʡ�
	*���������������������ɣ���ô�����֮�����»�����������
	*����������ı�����������ĸҪСд��
	*
	*������
	*������Ҫ���ñ�ʾ�����Ķ���Ϊ������ûʲô����Ļ��������������ʡ�
	*һ���Դ�д��ĸ��ͷ��
	*�ɶ��������ɵ����ƣ��䵥���뵥��֮�������Ҫͨ����д��������ĸ��ʵ�֡�
	*ʹ�õĶ��ʣ������ܱ�ﺯ��ʵ�ʵĲ����͹��ܡ�
	*��ʹ����a��b��c��û����������ʡ�
	*
	*������
	*��#define�ĳ�����ȫ���ô�д��
	*��enum��������ö���ͳ���ȫ���ô�д��
	*�ɶ��������ɵ����ƣ������뵥��֮�����»��������֡�
  */
	
	
	/**	
	*�ļ�ǰͷ��������ע������
	*�Ŀ	   	��ʽ/����
	*�ļ���		����ʽ��	@file	�ļ���
	*			�����ݡ� 	�����ļ���
	*			            ���ļ�������������뵽ע����Ͳ������ļ�����ʾ��
	*
	*ժҪ˵��	����ʽ �� @brief ժҪ˵��
	*			�����ݡ�  ��ʾ�ļ����ݵ�����
	*			  		  ������ܵ��ļ� etc.
  */
	


/*=====================================================================================================================*/
	
	
	
/**	
	*����ǰͷ��������ע������
	*�Ŀ��	��ʽ/����
	*ժҪ˵��	����ʽ�� @brief  ժҪ˵��
	*					�����ݡ���ʾ�������ܵ�����
	*��				 ��  ����oo���ܺ����� ��
	*
	*�������	����ʽ�� @param [in] ������  ˵��
	*					�����ݡ�  ���������˵��
	*
	*�������	����ʽ�� @param [out]������ �h��
	*					�����ݡ�  ���������˵��
	*
	*�������	����ʽ�� @param [in,out] ������ ˵��
	*					�����ݡ�  �������������˵��
	*
	*����ֵ		����ʽ�� @return����ֵ��˵��
	*					�����ݡ�	void������û�е����д��û�л����ޡ�
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
*�涨�йش�����({ })���������հ׵���д��ʽ
*������ ���� ������λ��
*ͳһ�������壬���ƽṹ��for��if-else��while�ȣ����ṹ�����ʹ�õģ�������д�����������Ե����������ο�����������
*���ƽṹ��for��if-else��while�ȣ��У�ֻҪ��ԭ�ļ�����û�����ƣ����в��輴���ǽ�һ��Ҳ��ʡ�ԣ���������Ϊ׷�����в���ʱ���п��ܳ������⣩

*��ע�͡�
*(1) ���庯����ʱ�򣬿�ʼ���K�ˣ�������Ӧ��ͬһ�С�
*	��������������
*	{ 
*		��������
*		��;
*	}
*	
*(2) �������ƽṹ��for��if-else��while�ȣ��ͽṹ���У���ʾ��ʼ�ģ�������Ӧ�ڿ�ʼ��ĩ�ˡ���ע�ͳ��⣩
*	if������{
*	  ��;
*	��
*	else if(��){
*		 ��;
*		 ��
*		 else{
*		 ��;
*		 ��
*
* ����
*(3) ������׼Ϊ4���ַ���ȵ�TAB��
* 
* ��ӿո�ķ���
*(4) ˫Ŀ������Լ�3Ŀ�������ǰ��Ҫ��ӿո񡣵��ǣ�������������⡣
*
*[ ]�� ->�� .( ���)�� ,( ���������)
*(5) ��Ŀ�������������֮�䲻�ո���ӿո�
*/				
				
/*=====================================================================================================================*/			
	
/*�жϷ���
�ж���	���ȼ�	��;
UART5 	12 			BLE
UART3 	15			Ũ�ȴ�����

TIMER3 	3				�ṩ10ms��100msʱ��
TIMER4 	4				����������ⲿ�ж�
TIMER5 	5				����������
TIMER6 	6				ʱ���ۻ�
TIMER7 	7				ADC�ɼ�
TIMER8 	8				����

*/


/*��ȡģ��ʽ
����
����ʽ
C51

*/

/******************* (C) COPYRIGHT 2023 Medris R&D *****END OF FILE****/
	