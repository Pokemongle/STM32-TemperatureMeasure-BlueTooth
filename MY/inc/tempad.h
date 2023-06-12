#ifndef __TEMPAD_H
#define __TEMPAD_H

/* define */
#define V25 0x6EE	
#define Avg_Slope 0x05
#define ADC1_DR_Address ((u32)0x40012400+0x4c)

/* include */
#include "stm32f10x.h"

/* variable */
extern __IO uint16_t ADC_ConvertedValue; // 采集到的12位AD值
extern double Current_Temp;// 当前温度值

/* function */
void Temp_ADC1_Init(void);
void ADC1_GPIO_Config(void);
void ADC1_Mode_Config(void);

#endif
