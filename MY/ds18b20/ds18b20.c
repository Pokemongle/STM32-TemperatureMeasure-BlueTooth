#include "ds18b20.h"
#include "delay.h"

void DS18B20_IO_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//DQ=PG11的输入模式
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	
}

void DS18B20_IO_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//DQ=PG11输出模式
	GPIO_Init(GPIOG,&GPIO_InitStructure);
}

void DS18B20_Reset(void)	   
{                 
	DS18B20_IO_OUT(); // SET PG11 输出模式
	DS_SetL; //拉低DQ
	Delay_us(750);    // 拉低750us  最少480us
	DS_SetH; //DQ=1 
	Delay_us(15);     //15US
}


u8 DS18B20_Check(void) 	   // 等待是否响应
{   
	u8 retry=0;// 记录时间的变量
	DS18B20_IO_IN();//SET PG11 INPUT 输入模式
    while ( DS_PIN &&retry<200)
	{
		retry++;
		Delay_us(1);
	};
	if(retry>=200)return 1;//如果200us还没有检测到拉低，说明不存在
	else retry=0;//可能存在，将计数器置零，还要再判断是不是拉低大概240us
    while ( !DS_PIN && retry < 240)
	{
		retry++;
		Delay_us(1);
	};//置高跳出
	if(retry>=240)return 1;// 一直拉低超过240us，说明可能不是由传感器产生的拉低
	
    return 0;
}


u8 DS18B20_Read_Bit(void) // 读一位
{
	u8 data;
	DS18B20_IO_OUT();//SET PG11 OUTPUT
	DS_SetL; // 主机拉低
	Delay_us(2);
	DS_SetH; 
	DS18B20_IO_IN();//SET PG11 INPUT
	Delay_us(12);
	if(DS_PIN)data=1;
	else data=0;	 
	Delay_us(50);           
	return data;
}


u8 DS18B20_Read_Byte(void)    // 读一个字节
{        
    u8 i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}


void DS18B20_Write_Byte(u8 dat)     
{             
	u8 j;
  u8 testb;// 记录取出来的每一位，低位在前
	DS18B20_IO_OUT();//SET PG11 OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS_SetL;// Write 1
            Delay_us(2);                            
            DS_SetH;
            Delay_us(60);             
        }
        else 
        {
            DS_SetL;// Write 0
            Delay_us(60);             
            DS_SetH;
            Delay_us(2);                          
        }
    }
}


void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Reset();	   
		DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0x44);// convert
} 

u8 DS18B20_Init(void){
		GPIO_InitTypeDef  GPIO_InitStructure;
 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Init(GPIOG,&GPIO_InitStructure);
	 
		DS18B20_Reset();
    return DS18B20_Check();// 查看是否有响应
}


float DS18B20_GetTemperture(void)
{
    u16 temp;
	u8 a,b;
	float value;
    DS18B20_Start();                    // ds1820 start convert
    DS18B20_Reset();
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0xbe);// convert	    
    a=DS18B20_Read_Byte(); // LSB   
    b=DS18B20_Read_Byte(); // MSB   
	temp=b;
	temp=(temp<<8)+a;
  if((temp&0xf800)==0xf800)//温度为负，前5为全为1
	{
		temp=(~temp)+1;
		value=temp*(-0.0625);
	}
	else
	{
		value=temp*0.0625;	
	}
	return value;    
}
