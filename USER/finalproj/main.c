#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "tempad.h"
#include "usart1.h"
#include "ds18b20.h"

int main(void){
		
		USART1_Init();	// 串口通道1初始化
		Temp_ADC1_Init(); // 通过STM32芯片进行实际温度测量
		SysTick_Init();	// 系统时钟初始化
		LED_Init();
		LED2_OFF;
		LED3_OFF;
		
		/* double output test*/
		printf("\r\n ----DS18B20 测温测试---- \r\n");
		float temper;
		while(DS18B20_Init())
		{
			printf("\r\n State: DS18B20 error \r\n");
			Delay_ms(500);
		}
		printf("\r\n State: DS18B20 normal \r\n");
		
		while(1){
				temper=DS18B20_GetTemperture();
				if(temper < 0){
						printf("\r\n Measured T:- %.2f℃ \r\n", temper);
				}else{
						printf("\r\n Measured T: %.2f℃ \r\n", temper);
				}
				Current_Temp= (1.43-ADC_ConvertedValue*3.3/4096)*1000 / 4.3+ 23 ;
				//Current_Temp=((double)V25-(double)ADC_ConvertedValue)/(double)Avg_Slope+23;
				printf("\r\n Real T= %.2f ℃ \r\n", Current_Temp);
				printf("\r\n --------------------- \r\n");
				Delay_ms(500);
		}

		/*--- DS18B20 responding test ---*/
		// OK
		/*
		printf("\r\n ----DS18B20 responding test---- \r\n");
		DS_ON;
		while(1){
				DS_Reset();
				if(!DS_Check()){
						printf("\r\n State: Available \r\n");
				}else{
						printf("\r\n State: Not Available \r\n");
				}
				Delay_ms(1000);
		}
		*/
		
		/*--- DS18B20 temperature test ---*/
		/*
		printf("\r\n ----DS18B20 temperature test---- \r\n");
		DS_ON;
		
		while(1){
				Delay_ms(500);
				//printf("\r\n Current T(℃)：%f \r\n", DS_Read_Temp());
				printf("\r\n Current T(℃)：%x \r\n", DS_Read_Temp_Test());
		}
		*/
		
		// test hex output
		/*
		while(1){
				Delay_ms(1000);
				printf("\r\n %X \r\n", 0x6D);
		}
		*/
		
}	
