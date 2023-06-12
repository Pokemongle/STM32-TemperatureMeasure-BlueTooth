#ifndef __DS18B20_H
#define __DS18B20_H

/* include */
#include "stm32f10x.h"

/* function */
void DS18B20_IO_IN(void);
void DS18B20_IO_OUT(void);
void DS18B20_Reset(void);
u8 DS18B20_Check(void);// 等待是否响应
u8 DS18B20_Read_Bit(void);// 读一位	
u8 DS18B20_Read_Byte(void);// 读一个字节
void DS18B20_Write_Byte(u8 dat);
void DS18B20_Start(void);// ds1820 start convert
u8 DS18B20_Init(void);
float DS18B20_GetTemperture(void);

/* define */
#define STATE_AVAILABLE 0
#define STATE_NOTAVAILABLE 1
#define DS_SetH GPIO_SetBits(GPIOG,GPIO_Pin_11)
#define DS_SetL GPIO_ResetBits(GPIOG,GPIO_Pin_11)
#define DS_ON RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE)// 打开PG口时钟
#define DS_PIN GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11)

#endif
