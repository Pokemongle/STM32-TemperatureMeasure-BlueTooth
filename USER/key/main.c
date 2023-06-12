/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：按键控制LED闪烁，S1取反LED2，S2取反LED3，S3同时取反LED2，LED3
          S4使LED2，LED3闪烁5次
硬件平台：尼莫M3S开发板
编写整理：shifang
固件库  ：V3.5
技术论坛：www.doflye.net
备    注：通过简单修改可以移植到其他开发板，部分资料来源于网络。
---------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"

int main(void)
{
	
  uint8_t j; //定义变量
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
	
  while (1)
  {
		if(!S1)
		{
			Delay_ms(10);
			if(!S1)	
				
			{
				 while(!S1);//等待按键释放
				 LED2_REV;
				
			}
		}
		
		////////////////////////////////////////////
		if(!S2)
		{
			Delay_ms(10);
			if(!S2)	
				
			{
				 while(!S2);
				 LED3_REV;
				
			}
		}
		//////////////////////////////////////////
		if(!S3)
		{
			Delay_ms(10);
			if(!S3)	
				
			{
				 while(!S3);
				 LED2_REV;
				 LED3_REV;
			}
		}
	///////////////////////////////////////////
	 if(S4)
		{
			Delay_ms(10);
			if(S4)	
				
			{
				 while(S4);
				 for(j=0;j<10;j++)
				{
				 LED2_REV;
				 LED3_REV;
				 Delay_ms(100);
				}
			}
		}

  }
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
