#include "sys.h"
#include "delay.h"
#include "musart.h"
#include "timer.h"
#include "spi.h"
#include "drv8889.h"
#include "ucommand.h"
#include "motor.h"
#include "force.h"
#include "led.h"
#include "beep.h"
#include "queue.h"

u8 CheckUartCommand(void);

u32 flag = 0;

CanTxMsg  TxMessage;
CanRxMsg  RxMessage;


 int main(void)
 {		
	delay_init(168);
 	delay_ms(500);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 
	uart1_Init(115200);	
	uart3_Init(115200);  
	OUTPUT_Init();
	TIM6_Init(CYCLE_1000 ,TIME_PRESCALER_84);
	MotorInit();
	M8128_Init();
 	while(1)
	{
				CheckUartCommand();
//			M8128_Config();	
	}
}


