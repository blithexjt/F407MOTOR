
#include "sys.h"
#include "musart.h"	

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif

volatile u16 com1_rx_len ;
volatile u8 com1_recv_end_flag ;
u8 com1_rx_buffer[USART_MAX_LEN];

UART3_Receive  uart3_rx;

static UART3_Receive uart3_data[Uart3Array_Len];


void uart1_Init(u32 bound)
{
    //GPIO????
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	  DMA_InitTypeDef DMA_InitStructure;



    USART_DeInit(USART1);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 		//??GPIOA??
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);		//??USART1??
    //??1????????
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); 	//GPIOA9???USART1
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);	 //GPIOA10???USART1
    //USART1????
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9; 	//GPIOA10?GPIOA9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//??100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 				//??????
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 				//??
    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//???PA9,PA10
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//??50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //??????
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //??
		GPIO_Init(GPIOA,&GPIO_InitStructure); //???PA8
    //USART1 ?????
    USART_InitStructure.USART_BaudRate = bound;					//?????
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//???8?????
    USART_InitStructure.USART_StopBits = USART_StopBits_1;		//?????
    USART_InitStructure.USART_Parity = USART_Parity_No;			//??????
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//????????
    USART_InitStructure.USART_Mode =  USART_Mode_Rx | USART_Mode_Tx;				//????
    USART_Init(USART1, &USART_InitStructure); 	//?????1

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;       //??1????
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //?????2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;	    //????1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ????
    NVIC_Init(&NVIC_InitStructure);							//??????????VIC????
    
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream5_IRQn; //?????DMA2_Stream5_IRQn
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //?????? 2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //?????? 2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //??????
    NVIC_Init(&NVIC_InitStructure);


    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);  	//????????
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);  	// ????DMA??

    /* ????DMA??*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  					// ??DMA??
    DMA_DeInit(DMA2_Stream5);
    DMA_InitStructure.DMA_Channel = DMA_Channel_4; 							//????
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;		//DMA????
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)com1_rx_buffer;		//DMA ???0??
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;   				//????????
    DMA_InitStructure.DMA_BufferSize = USART_MAX_LEN;						//?????
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//???????
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//???????
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //??????:8?
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//???????:8?
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							//??????
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;				    //?????
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;           //FIFO??
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;				//?????????
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;		//????????
    DMA_Init(DMA2_Stream5, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream5, ENABLE); //??DMA2_Stream5??

    USART_Cmd(USART1, ENABLE);  //????1
    USART1_Receive_En(1);

}



void USART1_IRQHandler(void)  												//??1??????
{
    if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET) 	//??????
    {
    	com1_recv_end_flag = 1;  	// ????????1

    	DMA_Cmd(DMA2_Stream5, DISABLE);  					   /* ????dma,?????? */
    	com1_rx_len = USART_MAX_LEN - DMA_GetCurrDataCounter(DMA2_Stream5);/* ?????????? ?????*/
    	DMA_ClearFlag(DMA2_Stream5,DMA_FLAG_TCIF5);  		/* ?DMA??? */
    	DMA_SetCurrDataCounter(DMA2_Stream5,USART_MAX_LEN);	/* ???????,??????????????????? */
    	DMA_Cmd(DMA2_Stream5, ENABLE);      				/*??DMA*/
    	USART_ReceiveData(USART1);   						//?????????(????????????)

    }

  	if(USART_GetFlagStatus(USART1,USART_IT_TXE)==RESET)	//??????
  	{
    	USART_ITConfig(USART1,USART_IT_TC,DISABLE);
		}
}




void uart3_Init(u32 bound)
{
	//GPIO????
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;



	USART_DeInit(USART3);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 		//??GPIOA??
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);		//??USART1??

	//??1????????
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); 	//GPIOA9???USART1
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);	 //GPIOA10???USART1
	//USART1????
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9; 	//GPIOA10?GPIOA9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//??100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 				//??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 				//??
	GPIO_Init(GPIOD,&GPIO_InitStructure); 						//???PA9,PA10

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//??50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //??
	GPIO_Init(GPIOD,&GPIO_InitStructure); //???PA8
	//USART1 ?????
	USART_InitStructure.USART_BaudRate = bound;					//?????
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//???8?????
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		//?????
	USART_InitStructure.USART_Parity = USART_Parity_No;			//??????
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//????????
	USART_InitStructure.USART_Mode =  USART_Mode_Rx | USART_Mode_Tx;				//????
	USART_Init(USART3, &USART_InitStructure); 	//?????1

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;       //??1????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //?????2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;	    //????1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ????
	NVIC_Init(&NVIC_InitStructure);							//??????????VIC????

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream1_IRQn; //?????DMA2_Stream5_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //?????? 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //?????? 2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //??????
	NVIC_Init(&NVIC_InitStructure);


	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);  	//????????
	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);  	// ????DMA??

	/* ????DMA??*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  					// ??DMA??
	DMA_DeInit(DMA1_Stream1);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4; 							//????
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;		//DMA????
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)(&uart3_data[0].com3_rx_buffer);		//DMA ???0??
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;   				//????????
	DMA_InitStructure.DMA_BufferSize = DMA_USART3_TX_BUF_LEN;						//?????
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//???????
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//???????
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //??????:8?
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//???????:8?
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							//??????
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;				    //?????
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;           //FIFO??
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;				//?????????
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;		//????????
	DMA_Init(DMA1_Stream1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Stream1, ENABLE); //??DMA2_Stream5??

	USART_Cmd(USART3, ENABLE);  //????1
	USART3_Receive_En(1);

}



void USART3_IRQHandler(void)  												//??1??????
{
	static u8 rcv_id = 0;
	if(USART_GetITStatus(USART3,USART_IT_IDLE)!=RESET) 	//??????
	{
		DMA_Cmd(DMA1_Stream1, DISABLE);  					   /* ????dma,?????? */
		uart3_data[rcv_id].com3_rx_len = USART_MAX_LEN - DMA_GetCurrDataCounter(DMA1_Stream1);/* ?????????? ?????*/
		uart3_data[rcv_id].DataSta = UartData_Vaild;
		DMA_ClearFlag(DMA1_Stream1,DMA_FLAG_TCIF1);  		/* ?DMA??? */
		rcv_id++;
		if(rcv_id >= Uart3Array_Len)
			rcv_id = 0;
		DMA_SetCurrDataCounter(DMA1_Stream1,DMA_USART3_TX_BUF_LEN);	/* ???????,??????????????????? */ 
		DMA1_Stream1->M0AR = (uint32_t)(&uart3_data[rcv_id].com3_rx_buffer);  
		DMA_Cmd(DMA1_Stream1, ENABLE);      	
		USART_ReceiveData(USART3); 
  }

  if(USART_GetFlagStatus(USART3,USART_IT_TXE)==RESET)	//??????
    	USART_ITConfig(USART3,USART_IT_TC,DISABLE);
	
}



void USART3_Receive_En(u8 rev_en)
{
	if(rev_en)
			GPIO_ResetBits(GPIOD,  GPIO_Pin_10);
	else
			GPIO_SetBits(GPIOD,  GPIO_Pin_10);
}
void USART1_Receive_En(u8 rev_en)
{
	if(rev_en)
		GPIO_ResetBits(GPIOA,  GPIO_Pin_8);
	else
		GPIO_SetBits(GPIOA,  GPIO_Pin_8);
}


void USART3_SendString( u8 *DataString)
{
	int i =0;
	//USART_ClearFlag( USART3, USART_FLAG_TC);
	while(DataString[i] != '\0')
	{
		while((USART3->SR&0X40)==0);
		USART_SendData( USART3, DataString[i++]);
	}
}

UART3_Receive* GetUart3Buffer(u8 revid)
{
	return &uart3_data[revid];
}

