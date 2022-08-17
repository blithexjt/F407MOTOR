#ifndef __DELAY_H
#define __DELAY_H 			   
#include <sys.h>	  

typedef struct
{
	u32 TIM_delayms;
	u32 count ;
	u8 state;

}TIM_Delay;

#define DelayMAX 1000
#define Delay_40_ms  40



void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

u8 delay_TimInit(TIM_Delay*  delay,u32 delayms,u8 enable);	

#endif





























