#ifndef __MUSART_H
#define __MUSART_H
#include "sys.h"
#include "musart.h"
#include "motor.h"
#include "force.h"

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

typedef struct
{
	double m_dEngValue[M812X_CHN_NUMBER];
	u8 MotorX_STL_Status;
	u8 MotorY_STL_Status;
}Debug_Paramet;


u8 CheckUartCommand(void);
u8 GetUartParameter(char *pInstr,double *pdBuffe,u8 ParametNum);

void Debug_printf(void);


#endif
