#include "motor.h"
#include "timer.h"
#include "drv8889.h"
#include "delay.h"
#include "musart.h"	

 //u8 g_USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
// u8 g_DATA_BUF1[DATA_BUFFER_LEN];
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
 u16 g_USART_RX_STA;       //接收状态标记	
 u16 g_DATA_TX_STA;
 u16 g_DMA_TX_STA;


 void MotorSetCurrent(u8 Motor, u8 current)
{
	u8 temp1 = Motor;
	u8 temp2 = current;
	#ifdef DRV8889
	Drv8889_SetCurrent (temp1,temp2);

	#else


	#endif
	
}

void MotorRun(u8 Motor, u32 current,double speed, float length)
{
	u32 pulse;
	int num = length*(200*32);
	switch(Motor)
	{
		case Motor_x:	TIM_CtrlPWMOutputs(TIM4, ENABLE);break;
		case Motor_y:	TIM_CtrlPWMOutputs(TIM10, ENABLE);break;
	}
	MotorSetCurrent( Motor, current);
	MotorSetSpeed( Motor, speed);
	if(0 == num) return;
	if(num < 0)
	{
		num = -num;
		MoveBackward (Motor, num);
	}
	else
	{
		MoveForward(Motor, num);
	}

//	Pulse_output(Motor,CYCLE_1000,num);


}

void MotorStart(u8 MotorNum,double current)
{
		switch(MotorNum)
		{
			case	Motor_x:
												DRV8889_EN_X_en();
												MotorSetCurrent( MotorNum, current);
												break;
			case	Motor_y:
												DRV8889_EN_Y_en();
												MotorSetCurrent( MotorNum, current);
												break;
		}
}


void MotorStop(u8 MotorNum,double current)
{
	if(0 == current)
	{
		switch(MotorNum)
		{
			case	Motor_x:
											TIM_CtrlPWMOutputs(TIM4, DISABLE);
											break;
			case	Motor_y:
											TIM_CtrlPWMOutputs(TIM10, DISABLE);
											break;
		}
	}
	MotorSetCurrent( MotorNum, current);
}	


void MotorSetSpeed(u8 motor,double speed)
{
	u8 arr = 0;
	u8 ccr = 0;
	TIM_TypeDef* TIMER;
	arr = speed*200*32;
	ccr = arr/2;
	
	if(motor == Motor_x)
	{	
			if(0 == speed)
			{
				TIM_CtrlPWMOutputs(TIM4, DISABLE);
				return;
			}
		TIMER = TIM4;
	}
	if(motor == Motor_y)   
	{
			if(0 == speed)
			{
				TIM_CtrlPWMOutputs(TIM10, DISABLE);
				return;
			}
		TIMER = TIM10;
	}
	TIM_update(TIMER,arr,ccr,AutoUpdate);	
}

void MotorInit()
{
	DRV8889_Init();

	
	
}

void MoveBackward(u8 Motor, u32 step)
{
	u32 pulse = step;
	switch(Motor)
	{
		case Motor_x:  MOTORX_DIR_Backward();		Pulse_output(Motor_x,CYCLE_1000,pulse);break;
		case Motor_y:  MOTORY_DIR_Backward();		Pulse_output(Motor_y,CYCLE_1000,pulse);break;
	}
}

void MoveForward(u8 Motor, u32 step)
{
	u32 pulse = step;
	switch(Motor)
	{
		case Motor_x:  MOTORX_DIR_Forward();		Pulse_output(Motor_x,CYCLE_1000,pulse);break;
		case Motor_y:  MOTORY_DIR_Forward();		Pulse_output(Motor_y,CYCLE_1000,pulse);break;
	}	
	Pulse_output(Motor,CYCLE_1000,pulse);
}

