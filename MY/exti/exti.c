#include "exti.h"
void EXTI_PA0_Config(){
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		/*config the extiline clock(PA0) and AFIO clock*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
		/*config the NVIC(PA0)*/
		NVIC_Config();
		/*config GPIO*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // up pull input
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		/* EXTI line(PE4) mode config */
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
		EXTI_InitStructure.EXTI_Line = EXTI_Line0;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
}
void EXTI_PE4_Config(){
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		/*config the extiline clock(PE4) and AFIO clock*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,ENABLE);
		/*config the NVIC(PE4)*/
		NVIC_Config();
		/*config GPIO*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // up pull input
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		/* EXTI line(PE4) mode config */
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
		EXTI_InitStructure.EXTI_Line = EXTI_Line4;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
}


static void NVIC_Config(void){
			NVIC_InitTypeDef NVIC_InitStructure;
			/*Config 1 bit for preemption priority*/
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
			/*Config P[A|B|C|D|E]4 as interrupt source*/
			NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
}
