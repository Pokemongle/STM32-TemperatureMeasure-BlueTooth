#include "usart1.h"

void USART1_Init(void){
		GPIO_InitTypeDef GPIO_InitStructure; 
		USART_InitTypeDef USART_InitStructure;
		/* config USART1 clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
		/* USART1 GPIO config */
		/* Configure USART1 Tx (PA.09) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/* Configure USART1 Rx (PA.10) as input floating */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/* USART1 mode config */
		USART_InitStructure.USART_BaudRate = 115200; 
		USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
		USART_InitStructure.USART_StopBits = USART_StopBits_1; 
		USART_InitStructure.USART_Parity = USART_Parity_No ; 
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		/* Enable USART */
		USART_Init(USART1, &USART_InitStructure);
		USART_Cmd(USART1, ENABLE);
}

uint8_t SendBuff[SENDBUFF_SIZE];
void DMA_Config(void){
		DMA_InitTypeDef DMA_InitStructure;
	
		/* 1. 开启DMA时钟 */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		NVIC_Config(); //配置DMA中断
	
		/* 2. 填充初始化结构体 */
		/* 设置DMA源：内存地址&串口数据寄存器地址 */
		DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
		/* 内存地址（要传输的变量的指针）*/
		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
		/* 方向：从内存到外设 */
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		/* 传输大小 DMA_BufferSize = SENDBUFF_SIZE */
		DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
		/* 外设地址不增 */
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		/* 内存地址自增 */
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		/* 外设数据单位 */
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		/* 内存数据单位 8bit*/
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		/* DMA模式：一次传输 */
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		/* 优先级：中 */
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
		/* 禁止内存到内存的传输 */
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_Init(DMA1_Channel4, &DMA_InitStructure);
		
		/* 3. Enable */
		/* 配置DMA1的4通道 */
		DMA_Cmd (DMA1_Channel4,ENABLE);/* 使能DMA */
		DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);/* 配置DNA发送完成后产生中断 */	
}

static void NVIC_Config(void){
		NVIC_InitTypeDef NVIC_InitStructure;
	
		/* Configure one bit for preemption priority */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
		/* 配置P[A|B|C|D|E]0为中断源 */
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...){
	const char *s; 
	int d;
	char buf[16]; 
	va_list ap; 
	va_start(ap, Data); 
	while ( *Data != 0) // ????????????
	{
		if( *Data == 0x5c ) //'\' 
		{
			switch ( *++Data ) 
			{ 
				case 'r': //???
				USART_SendData(USARTx, 0x0d); 
				Data++; 
				break; 

			 case 'n': //???
			 USART_SendData(USARTx, 0x0a);
			 Data ++; 
			 break; 

			 default: 
			 Data ++; 
			 break; 
			}
		}
	else if( (*Data) == '%') 
	{ // 
		switch ( *++Data ) 
		{
			 case 's': //???
			 s = va_arg(ap, const char *); 
			 for ( ; *s; s++)
			 { 
				 USART_SendData(USARTx,*s); 
				 while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
			 } 
			 Data++; 
			 break; 
			 case 'd': //???
			 d = va_arg(ap, int); 
			 itoa(d, buf, 10); 
			 for (s = buf; *s; s++)
			 { 
				 USART_SendData(USARTx,*s); 
				 while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
			 } 
			 Data++; 
			 break; 
			 default: 
			 Data++; 
			 break; 
		}
 } /* end of else if */
 else USART_SendData(USARTx, *Data++); 
 while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET ); 
 }	
}

/* 重定向printf */
int fputc(int ch, FILE* f){
		/*将Printf内容发往串口*/
		USART_SendData(USART1, (unsigned char) ch);
		while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);//等待发送完毕
		return(ch);
}

/* 将整形数据转换成字符串，被USART1_printf调用 */
static char* itoa(int value, char *string, int radix){
		int i, d;
		int flag = 0; 
		char *ptr = string; 

		/* This implementation only works for decimal numbers. */
		if (radix != 10) 
		{ 
				*ptr = 0; 
				return string; 
		} 

		if (!value) 
		{ 
				*ptr++ = 0x30; 
				*ptr = 0; 
				return string; 
		} 

		/* if this is a negative value insert the minus sign. */
		if (value < 0) 
		{ 
			 *ptr++ = '-'; 
			 /* Make the value positive. */
			 value *= -1; 
		} 
		for (i = 10000; i > 0; i /= 10) 
		{ 
			 d = value / i; 
			 if (d || flag) 
			 { 
					*ptr++ = (char)(d + 0x30); 
					value -= (d * i); 
					 flag = 1; 
			 } 
		} 

		/* Null terminate the string. */
		*ptr = 0; 
		return string; 
} /* NCL_Itoa */
