#include "stm32f10x.h"
#include "usart1.h"
#include "delay.h"
#include "led.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];
uint16_t i;

int main(void){
		USART1_Config();
		LED_Init();
		DMA_Config();
		SysTick_Init();
		
		LED2_OFF;
		LED3_OFF;
	
		/* 填充将要发送的数据 */
		for(i=0;i<SENDBUFF_SIZE;i++){
			SendBuff[i] = 0xff;
		}
		LED2_Spark();
		
		/* 串口向DMA提出请求 */
		USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
		
		
		while(1);
}
