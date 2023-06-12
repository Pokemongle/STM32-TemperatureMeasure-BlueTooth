#include "pwm.h"

/** @brief TIM3输出信号初始化，调用函数，TIM3四个通道就会有PWM信号输出
	* @param void
	*
	*/
void TIM3_PWM_Init(u16 per, u16 pse){
		// GPIO configuration
		GPIO_InitTypeDef GPIO_InitStructure;
		/*使能TIM3时钟*/
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		/*TIM3 部分重映射*/
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//TIM3部分重映射 TIM3_CH2->PB5
		/*GPIOB Config, TIM3 channel 2*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽模式
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
		// mode configuration
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
		TIM_OCInitTypeDef TIM_OCInitStructure;

		/* PWM 点电平跳变值 */
		u16 CCR2_Val = 500;
		
		/* Time base configuration */
		//定时器计数per次为一个周期
		TIM_TimeBaseStructure.TIM_Period = per;
		//设置预分频，不预分频，为72MHz
		TIM_TimeBaseStructure.TIM_Prescaler = pse;
		//设置时钟分频系数，不分频
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
		//向上计数模式
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
		/* PWM output configuration */
		//配置为PWM模式1
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		//有效电平为高电平
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		/* PWM1 Mode configuration: Channel2 */
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		//设置通道2的电平跳变值
		//TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
		//使能通道2
		TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

		// 使能通道 TIM3 重载寄存器 ARR
		TIM_ARRPreloadConfig(TIM3, ENABLE);
		 
		/* TIM3 enable counter */
		TIM_Cmd(TIM3, ENABLE); //使能定时器3
}

