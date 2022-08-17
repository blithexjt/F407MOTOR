#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    

#define CAN_TX_RX_MAX_LEN   8

typedef enum
{
    Buf_No1,
    Buf_No2,
}Receive_buff;
extern u8 CanBuffer[200];

//CAN1����RX0�ж�ʹ��
#define CAN1_RX0_INT_ENABLE	0		//0,��ʹ��;1,ʹ��.								    
										 							 				    
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
 
u8 CAN1_Send_Msg(u8* msg,u8 len);						//��������

u8 CAN1_Receive_Msg(char *Buffer);							//��������
#endif

















