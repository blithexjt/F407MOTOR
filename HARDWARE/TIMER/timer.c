#include "sys.h"
#include "musart.h"	
#include "delay.h"
#include "timer.h"
#include "motor.h"
#include "drv8889.h"

void RGBLED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

 	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1); 
 	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 
 	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_TIM1); 
 	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); 
 	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_TIM1); 
 	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1); 
 	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12\
								|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
}


void TIM1_PWM_Init()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//ʹ�ܶ�ʱ��4ʱ��

	TIM_TimeBaseStructure.TIM_Period = 1000;
	TIM_TimeBaseStructure.TIM_Prescaler = TIME_PRESCALER_84;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_Pulse = 10;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_Pulse = 10;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC2Init(TIM1, &TIM_OCInitStructure); 

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_Pulse = 10;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  

	TIM_OC1PreloadConfig(TIM1,  TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1,  TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1,  TIM_OCPreload_Enable);

	TIM_Cmd(TIM1,  ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

}


void TIM6_Init(u16 arr,u16 psc)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	 

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_Cmd(TIM6,  ENABLE);

}



void OUTPUT_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//ʹ��PORTFʱ��	
    
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4); //GPIOB7����Ϊ��ʱ��4   
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM10); //GPIOA0����Ϊ��ʱ��5
    
	GPIO_InitStructure.GPIO_Pin = Motor1_Step_Pin; //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //�����������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_Step_Port, &GPIO_InitStructure);//��ʼ��GPIO

	GPIO_InitStructure.GPIO_Pin = Motor2_Step_Pin; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //�����������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_Step_Port, &GPIO_InitStructure);//��ʼ��GPIOA
}



void TIM4_PWM_Init(u32 Cycle1)
{  

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_Motor1_Step, ENABLE);	//ʹ�ܶ�ʱ��4ʱ��
 
   //��ʼ��TIM4
	TIM_TimeBaseStructure.TIM_Period = Cycle1-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =TIME_PRESCALER_84; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM4 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_Pulse = Cycle1/2-1;//ռ�ձ�Ϊ50%
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC2
	 
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR2�ϵ�Ԥװ�ؼĴ���

	TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable);//TIM4Ϊ����ʱ��
	TIM_SelectOutputTrigger(TIM4, TIM_TRGOSource_Update);//
	TIM_ARRPreloadConfig(TIM4, ENABLE);
 
	TIM_Cmd(TIM4, ENABLE);  
	
}



void TIM3_PWM_Init(u32 PulseNum2)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 
  //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = PulseNum2; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_SelectInputTrigger(TIM3,TIM_TS_ITR3);
	TIM3->SMCR|=0x07;
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3,ENABLE);
}





void TIM10_PWM_Init(u32 Cycle2)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_Motor2_Step, ENABLE);	//ʹ�ܶ�ʱ��10
 
   //��ʼ��TIM10
	TIM_TimeBaseStructure.TIM_Period = Cycle2-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =TIME_PRESCALER_84; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM10 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_Pulse = Cycle2/2-1;
	TIM_OC1Init(TIM10, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM5 OC1

	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);  //ʹ��TIM5��CCR2�ϵ�Ԥװ�ؼĴ���

	TIM_SelectMasterSlaveMode(TIM10, TIM_MasterSlaveMode_Enable);
	TIM_SelectOutputTrigger(TIM10, TIM_TRGOSource_Update);
	TIM_ARRPreloadConfig(TIM10, ENABLE);
 
	TIM_Cmd(TIM10, ENABLE);  
	
}
void TIM9_PWM_Init(u32 PulseNum1)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);	 

	TIM_TimeBaseStructure.TIM_Period = PulseNum1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_SelectInputTrigger(TIM9,TIM_TS_ITR2);
	TIM9->SMCR|=0x07;
	TIM_ITConfig(TIM9, TIM_IT_Update, DISABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Pulse_output(u16 MotorNum,u32 Cycle,u32 PulseNum)
{
	switch (MotorNum)
	{
		case Motor_x:TIM4_Master_TIM3_Slave( Cycle,PulseNum);break;
		case Motor_y:TIM10_Master_TIM9_Slave( Cycle,PulseNum);break;
	}	
}
void TIM4_Master_TIM3_Slave(u32 Cycle1,u32 PulseNum1)
{
    TIM3_PWM_Init(PulseNum1);
    TIM_Cmd(TIM3, ENABLE);
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
    TIM4_PWM_Init(Cycle1);
    TIM_CtrlPWMOutputs(TIM4, ENABLE);   
  //  TIM_Cmd(TIM4, ENABLE);

}


void TIM10_Master_TIM9_Slave(u32 Cycle2,u32 PulseNum2)
{
		TIM9_PWM_Init(PulseNum2);
    TIM_Cmd(TIM9, ENABLE);
    TIM_ClearITPendingBit(TIM9,TIM_IT_Update);
    TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE);
    TIM10_PWM_Init(Cycle2);
    TIM_CtrlPWMOutputs(TIM10, ENABLE);   
 //   TIM_Cmd(TIM10, ENABLE);
	
}

void TIM1_BRK_TIM9_IRQHandler(void) 
{ 
    if (TIM_GetITStatus(TIM9, TIM_IT_Update) != RESET)     // TIM_IT_CC1
    {
        TIM_ClearITPendingBit(TIM9, TIM_IT_Update); // ����жϱ�־λ 
	      TIM_CtrlPWMOutputs(TIM10, DISABLE);  
        TIM_Cmd(TIM10, DISABLE); // �رն�ʱ�� 
        TIM_Cmd(TIM9, DISABLE); // �رն�ʱ�� 

		}   
}
void TIM3_IRQHandler(void) 
{ 
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)     // TIM_IT_CC1
    { 
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // ����жϱ�־λ 
				TIM_CtrlPWMOutputs(TIM4, DISABLE);  
        TIM_Cmd(TIM4, DISABLE); // �رն�ʱ�� 
        TIM_Cmd(TIM3, DISABLE); // �رն�ʱ�� 
     
	} 		
}


void TIM_Setcompare(u16 Cycle1,u16 Cycle2)
{
	TIM_SetCompare2(TIM4, Cycle1);
	TIM_SetCompare1(TIM10, Cycle2);
}


//update the  frequence of motor
void TIM_update(TIM_TypeDef * TIMx,u16 arr,u16 ccr,u8 option)
{
	TIM_UpdateDisableConfig(TIMx, ENABLE);
	TIMx->ARR = arr;
	if(TIM4 == TIMx)  TIMx->CCR1= ccr;	
	if(TIM10 == TIMx)  TIMx->CCR1= ccr;
	TIM_UpdateDisableConfig(TIMx, DISABLE);
	
	delay_ms(1);

	if(option == immediately)   TIM_GenerateEvent(TIMx, TIM_EventSource_Update);
}
