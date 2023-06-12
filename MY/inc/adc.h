#ifndef __ADC_H
#define __ADC_H

/* include */
#include "stm32f10x.h"
extern __IO uint16_t ADC_ConvertedValue;
/* function */
void ADC1_Init(void);
static void ADC1_GPIO_Config(void);
static void ADC1_Mode_Config(void);
void ADC1_Mode_Config(void);

/* define */
#define ADC1_DR_Address ((u32)0x40012400+0x4c)

#endif

