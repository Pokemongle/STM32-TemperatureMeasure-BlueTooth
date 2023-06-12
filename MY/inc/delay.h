#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_us(__IO u32 nTime);	  //单位10us
void TimingDelay_Decrement(void);
#define Delay_ms(x) Delay_us(1000*x)//单位ms

#endif 
/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
