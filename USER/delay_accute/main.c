#include "led.h"
#include "delay.h"
#include "stm32f10x.h"

int main(void){
		LED_Init(); //初始化LED
		LED2_ON;
		LED3_ON;
		SysTick_Init();//10us中断一次
		while(1){
				Delay_ms(500);
				LED2_REV;
				Delay_ms(500);
				LED3_REV;
		}
}
