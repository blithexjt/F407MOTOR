#ifndef __DRV8889_H
#define __DRV8889_H

#include "sys.h"
#define DIR_X_port      		GPIOD
#define Dir_X_pin	      		GPIO_Pin_3

#define DIR_Y_port      	GPIOD
#define Dir_Y_pin	      		GPIO_Pin_7


#define nFault_X_port   		GPIOD
#define nFault_X_pin    		GPIO_Pin_1

#define nFault_Y_port   		GPIOD
#define nFault_Y_pin    		GPIO_Pin_5

#define nSleep_X_port   		GPIOC
#define nSleep_X_pin    		GPIO_Pin_8

#define nSleep_Y_port   		GPIOC
#define nSleep_Y_pin    		GPIO_Pin_9

#define Drvoff_X_port   		GPIOD
#define Drvoff_X_pin	 		GPIO_Pin_2

#define Drvoff_Y_port   	GPIOD
#define Drvoff_Y_pin	 		GPIO_Pin_6


#define CS_X_port       		GPIOD
#define CS_X_pin        	GPIO_Pin_4

#define CS_Y_port       	GPIOG
#define CS_Y_pin        	GPIO_Pin_9


#define DRV8889_CS_X_L()	    			GPIO_ResetBits( CS_X_port, CS_X_pin)
#define DRV8889_CS_X_H()	    			GPIO_SetBits( CS_X_port, CS_X_pin)

#define DRV8889_CS_Y_L()	    		GPIO_ResetBits( CS_Y_port, CS_Y_pin)
#define DRV8889_CS_Y_H()	    		GPIO_SetBits( CS_Y_port, CS_Y_pin)

#define DRV8889_EN_X_en()	  		  GPIO_ResetBits( Drvoff_X_port, Drvoff_X_pin)
#define DRV8889_EN_X_dis()	 			GPIO_SetBits( Drvoff_X_port, Drvoff_X_pin)

#define DRV8889_EN_Y_en()		  		GPIO_ResetBits( Drvoff_Y_port, Drvoff_Y_pin)
#define DRV8889_EN_Y_dis()	 			GPIO_SetBits( Drvoff_Y_port, Drvoff_Y_pin)

#define DRV8889_SLEEP_X_EN()				GPIO_ResetBits( nSleep_X_port, nSleep_X_pin)
#define DRV8889_SLEEP_X_Dis() 			GPIO_SetBits( nSleep_X_port, nSleep_X_pin)

#define DRV8889_SLEEP_Y_EN()				GPIO_ResetBits( nSleep_Y_port, nSleep_Y_pin)
#define DRV8889_SLEEP_Y_Dis() 			GPIO_SetBits( nSleep_Y_port, nSleep_Y_pin)


typedef enum
{ 
	FAULT_Status = 0x00,
	DIAG_Status_1= 0x01,
	DIAG_Status_2= 0x02,
	CTRL1 = 0X03,
	CTRL2 = 0X04,
	CTRL3 = 0X05,
	CTRL4 = 0X06,
	CTRL5 = 0X07,
	CTRL6 = 0X08,
	CTRL7 = 0X09,
	CTRL8 = 0X0A,	
}REGISTER_MEMORY;

typedef enum
{
	stop,
	forward,
	backward,
}Motor_turn;

typedef enum
{
	CS_X,
	CS_Y,
}CS_NUM;

typedef enum
{
	MICROSTEP_FULL_100 = 0,
	MICROSTEP_FULL_71 ,
	MICROSTEP_2_NONCRR ,
	MICROSTEP_2,
	MICROSTEP_4,
	MICROSTEP_8,
	MICROSTEP_16,
	MICROSTEP_32,
	MICROSTEP_64,
	MICROSTEP_128,
	MICROSTEP_256,
}MICROSTEP;

typedef enum
{
	CURRENT_100_PERCENT = 0,
	CURRENT_93_75_PERCENT,
	CURRENT_87_5_PERCENT,
	CURRENT_81_25_PERCENT,
	CURRENT_75_PERCENT,
	CURRENT_68_75_PERCENT,
	CURRENT_62_5_PERCENT,
	CURRENT_56_25_PERCENT,
	CURRENT_50_PERCENT,
	CURRENT_43_75_PERCENT,
	CURRENT_37_5_PERCENT,
	CURRENT_31_25_PERCENT,
	CURRENT_25_PERCENT,
	CURRENT_18_75_PERCENT,
	CURRENT_12_5_PERCENT,
	CURRENT_6_25_PERCENT,
}CURRENT;

typedef enum
{
	IcrSlow_DcrSlow = 0,
	IcrSlow_DcrMixed_30_percent,
	IcrSlow_DcrMixed_60_percent,
	IcrSlow_DcrFast,
	Icr_Mixed_30_percent_DcrMixed_30_percent,
	Icr_Mixed_60_percent_DcrMixed_60_percent,
	Smart_Tune_Dynamic_Decay,
	Smart_Tune_Ripple_control,
}DECAY_MODE;



void DRV8889_Init(void);


void DRV8889_MotorRun(u8 Motor,u8 EnHoldCurrent);

//set motor microstep parament and write into drv8889 chip
void Drv8889_SetMotorMicrostep (u8 Motor,u8 microstep);

//set motor current parament and write into drv8889 chip
void Drv8889_SetCurrent (u8 Motor,u8 current);

//write value into address of drv8889 chip by spi method
void Drv8889_write(u8 Motor,u8 address,u8 value);

//read value out of address of drv8889 chip by spi method
u8 Drv8889_read(u8 Motor,u8 address);

void Drv8889_CS_EN(u8 CS);
void Drv8889_CS_DIS(u8 CS);

#endif
