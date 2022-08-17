#ifndef __MUSART_H
#define __MUSART_H
#include "sys.h"
#include "musart.h"
#include "motor.h"

typedef enum
{
	MOTORX_Current = 1,
	MOTORX_Speed,
	MOTORX_Start,
	MOTORX_Stop,
	MOTORX_Run,
	MOTORY_Current,
	MOTORY_Speed,
	MOTORY_Start,
	MOTORY_Stop,
	MOTORY_Run,
}UART_COMMAND;

typedef enum
{
	RX_END_Failed,
	RX_END_Success,
}RX_END_STA;

u8 CheckUartCommand(void);
u8 GetUartParameter(char *pInstr,double *pdBuffe,u8 ParametNum);




#endif
