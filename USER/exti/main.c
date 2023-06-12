/*
	文件描述：通过按键控制LED的亮灭
*/
#include "led.h"
#include "exti.h"
#include "stm32f10x.h"
#include "stm32f10x_it.h"
int main(void){
		/*Config the led*/
		LED_Init();
		LED2_ON;
		LED3_OFF;
		
		/*exti line config*/
		EXTI_PE4_Config();
		while(1);
}
