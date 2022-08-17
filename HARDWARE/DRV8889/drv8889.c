#include "drv8889.h"
#include "spi.h"
#include "timer.h"
#include "delay.h"


#define DRV_Delay_H()	delay_us(1000)
#define DRV_Delay_L() delay_us(1)

void DRV8889_Init()
{

	GPIO_InitTypeDef GPIO_InitStucture;
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitStucture.GPIO_Pin = Dir_X_pin|Dir_Y_pin;
	GPIO_InitStucture.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStucture.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStucture);

	GPIO_InitStucture.GPIO_Pin = nSleep_X_pin|nSleep_Y_pin;
	GPIO_InitStucture.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStucture.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStucture);
	
	GPIO_InitStucture.GPIO_Pin = nFault_X_pin|nFault_Y_pin;
	GPIO_InitStucture.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStucture.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStucture);

	GPIO_InitStucture.GPIO_Pin = Drvoff_X_pin|CS_X_pin|Drvoff_Y_pin;
	GPIO_InitStucture.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStucture.GPIO_OType = GPIO_OType_OD;    
	GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStucture);

	GPIO_InitStucture.GPIO_Pin = CS_Y_pin;
	GPIO_InitStucture.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStucture.GPIO_OType = GPIO_OType_OD;    
	GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStucture);
	
	SPI3_Init();
	delay_ms(2);

	DRV8889_CS_X_H();
	DRV8889_CS_Y_H();
	DRV_Delay_H();
//	DRV8889_SLEEP_X_Dis();
	DRV8889_SLEEP_Y_Dis();
	delay_ms(1);
	//DRV8889_EN_X_dis();
	//DRV8889_EN_Y_dis();
	DRV8889_EN_Y_en();
	delay_ms(1);

	Drv8889_SetMotorMicrostep(Motor_x,MICROSTEP_32);
	
	Drv8889_SetMotorMicrostep(Motor_y,MICROSTEP_32);
}

void DRV8889_MotorRun(u8 Motor,u8 EnHoldCurrent)
{
	Drv8889_SetCurrent (Motor,CURRENT_100_PERCENT);			
	Pulse_output(Motor,CYCLE_1000,PULSENUM_400);
	if(~(EnHoldCurrent))  Drv8889_SetCurrent (Motor,CURRENT_37_5_PERCENT);	
}



void Drv8889_SetMotorMicrostep (u8 Motor,u8 microstep)
{
  u8 temp1;
	u8 temp2 = microstep;
	temp1 = Drv8889_read( Motor,CTRL3);
	temp2 = temp2 | (temp1 & (0xf0)); 
	Drv8889_write( Motor,CTRL3,temp2);
	temp2 = Drv8889_read( Motor,CTRL3);
  delay_us(1);	
}

void Drv8889_SetCurrent (u8 Motor,u8 current)
{
	u8 temp1 = 0;
	u8 temp2 = (current<<4);
	temp1 = Drv8889_read(Motor,CTRL1);
	temp2 = temp2 | (temp1 & (0x0f)); 
	Drv8889_write(Motor,CTRL1,temp2);
	temp2 = Drv8889_read(Motor,CTRL1);
	delay_us(1);
}

void Drv8889_DisOut (u8 Motor,u8 disout)
{
	u8 temp1 = 0;
	u8 temp2 = (disout<<7);
	temp1 = Drv8889_read(Motor,CTRL2);
	temp2 = temp2 | (temp1 & (0x7f)); 
	Drv8889_write(Motor,CTRL2,temp2);
}


void Drv8889_write(u8 Motor,u8 address,u8 value)
{
	u8 temp = 0;
	u8 temp2 = value;
	temp = (address<<1);
	if(Motor == Motor_x)
	{
		Drv8889_CS_EN(CS_X);
		SPI3_ReadWriteByte(temp);
		SPI3_ReadWriteByte(temp2);
		Drv8889_CS_DIS(CS_X);
	}
	else if(Motor == Motor_y)
	{
		Drv8889_CS_EN(CS_Y);
		SPI3_ReadWriteByte(temp);
		SPI3_ReadWriteByte(temp2);
		Drv8889_CS_DIS(CS_Y);
	}
}



u8 Drv8889_read(u8 Motor,u8 address)
{
	u8 temp = 0;
	u8 value = 0;
	temp = (address<<1) | (0x40);
	if(Motor == Motor_x)
	{
		Drv8889_CS_EN(CS_X);
		SPI3_ReadWriteByte(temp);
		value = SPI3_ReadWriteByte(0xff);
		Drv8889_CS_DIS(CS_X);
	}
		else if(Motor == Motor_y)
	{
		Drv8889_CS_EN(CS_Y);
		SPI3_ReadWriteByte(temp);
		value = SPI3_ReadWriteByte(0xff);
		Drv8889_CS_DIS(CS_Y);
	}
	return value;
}

void Drv8889_CS_EN(u8 CS)
{
	switch(CS)
	{		
		case CS_X:  DRV8889_CS_Y_H();	DRV_Delay_H();DRV8889_CS_X_L();break;
		case CS_Y:	DRV8889_CS_X_H();	DRV_Delay_H();DRV8889_CS_Y_L();break;
	}
	DRV_Delay_L();
}

void Drv8889_CS_DIS(u8 CS)
{
	DRV_Delay_L();
	switch(CS)
	{		
		case CS_X:  DRV8889_CS_X_H();break;
		case CS_Y:	DRV8889_CS_Y_H();break;
	}
	DRV_Delay_H();
}