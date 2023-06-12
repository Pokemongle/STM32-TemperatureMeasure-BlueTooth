#include "stm32f10x.h"
#include "led.h"
#include "pwm.h"
#include "delay.h"

int main(void){
		LED_Init();
		SysTick_Init();
		LED3_ON;
		u32 period = 1500;
		u8 pwm_flag = 0;
		u16 i = 1;
		/* 使用延时 */
		while(1){
				Delay_us(i);
				LED3_REV;
				Delay_us(period - i);
				LED3_REV;
				if(!pwm_flag){//逐渐变亮
						i++;
				}
				else{
						i--;
				}
				if(i>=period-1-i){
						pwm_flag = 1;
				}		
				else if(i<=1){
						pwm_flag = 0;
				}
				
				
		}
		/** 使用TIM定时器
		u8 pwm_flag = 0;
		u16 i = 0;
		TIM3_PWM_Init(999,72-1);
		while(1){
				if(pwm_flag == 0){
						i++;
						if(i==100){
								pwm_flag = 1;
						}
				}
				else{
						i--;
						if(i==0){
								pwm_flag = 0;
						}
				}
				TIM_SetCompare2(TIM3,i);
				Delay_ms(5);
		}
		*/
}
