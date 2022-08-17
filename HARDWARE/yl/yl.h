#ifndef __YCOMMAND_H
#define __YCOMMAND_H
#include "sys.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "delay.h"
#include "musart.h"


typedef  u8  byte;

#define RX_BUFFER_SIZE	20
#define M812X_CHN_NUMBER	3

union DealDataFloat2Byte_TypeDef
{
	float m_FloatResultData;
	u8	  m_ByteResultDataBuffer[4];
};
typedef enum
{
	revok,
	revwait,
	timeout,
	txwait,
}TxRvState;

typedef enum
{
    AT_CMD_SMPR=0,
    AT_CMD_SGDM,
    AT_CMD_GOD,
    AT_CMD_GSD,
    AT_END,
}AT_Cmd;

typedef unsigned char(*pFunc)(unsigned char *ptr,unsigned char len);
typedef struct
{
    AT_Cmd cmd;
    unsigned char *str;
    pFunc cb;
}AT_cmd_fun;

typedef enum
{
	rx=0,
	tx,
}command_sta;

typedef enum
{
	 Read=1,
	 set,
	 getdata,
}M8128_Command_Format;


static double m_dEngValue[M812X_CHN_NUMBER];
static union DealDataFloat2Byte_TypeDef DealDataBufferUnion[M812X_CHN_NUMBER];


void M8128(void);

void RealTimeMode(bool mode);

u8 M8128_Config(void);

void M8128_Init(void);

u8 RevCommnd(void);

void SendCommand(	M8128_COMMAND  sgdm);

static u8 YGetChParameter(char *pInstr,double *pdBuffer,u8* com3_rx_ptr);

bool YGetEng(u8* com3_rx_ptr);

u8  AT_cmd_search( u8 *p);

#endif
