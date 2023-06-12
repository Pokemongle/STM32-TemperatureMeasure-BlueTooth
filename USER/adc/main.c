#include "stm32f10x.h"
#include "usart1.h"
#include "delay.h"
#include "adc.h"

/* ADC1转换的电压值通过DMA方式传输到SRAM */
extern __IO uint16_t ADC_ConvertedValue;

//局部变量，用于保存转换计算后的电压
float ADC_ConvertedValueLocal;

int main(void){
		USART1_Config();
		ADC1_Init();
		SysTick_Init();
		
		printf("\r\n -------这是一个ADC测试------\r\n");
		
		while(1){
				ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值
				printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue);
				printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal);
				Delay_us(0xfffff); // 延时
		}
}
