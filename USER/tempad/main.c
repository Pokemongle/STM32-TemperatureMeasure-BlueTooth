#include "stm32f10x.h"
#include "delay.h"
#include "exti.h"
#include "key.h"
#include "led.h"
#include "pwm.h"
#include "tempad.h"
#include "usart1.h"

int main(void){
		USART1_Init();	// 串口通道1初始化
		Temp_ADC1_Init(); // 通过STM32芯片进行实际温度测量
		SysTick_Init();		// 系统时钟初始化
		
		printf("\r\n 内部温度传感器实验 \r\n");
		printf( "\r\n Print current Temperature \r\n");
	
		while(1){
				Delay_us(0x1fffee);
				// 计算方法1，查表赋变量值
				//Current_Temp= (1.43-ADC_ConvertedValue*3.3/4096)*1000 / 4.3+ 25 ;
				// 计算方法2，自定义宏
				// -V25: 25℃对应的电压值
				// -Avg_Slope: 温度曲线平均斜率 单位：mV/℃
				Current_Temp=(V25-ADC_ConvertedValue)/Avg_Slope+25;
				// 10进制显示
				printf("\r\n The current temperature= %3d ℃ \r\n", Current_Temp);
				// 16进制显示
				//printf("\r\n The current temperature= %04x \r\n", Current_Temp);
		}
}
