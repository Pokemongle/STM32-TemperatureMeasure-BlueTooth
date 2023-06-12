#include "adc.h"

__IO uint16_t ADC_ConvertedValue; // 12位AD即时采样值

void ADC1_Init(void){
		ADC1_GPIO_Config();
		ADC1_Mode_Config();
}

static void ADC1_GPIO_Config(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		/* 1. clock */
		/* Enable DMA clock */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		/* Enable ADC1 and GPIOA clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
		
		/* 2. structure */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);// 输入时不用设置速率
	
}

static void ADC1_Mode_Config(void){
		DMA_InitTypeDef DMA_InitStructure;
		ADC_InitTypeDef ADC_InitStructure;
	
		/*-----------DMA channel1 configuration-----------*/
		DMA_DeInit(DMA1_Channel1);
	
		/* 2. structure */
		/* 外设基地址：ADC地址 */
		DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
		/* 内存地址 */
		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;
		/* 外设为数据来源 */
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		/* 传输大小 DMA_BufferSize = 1 */
		DMA_InitStructure.DMA_BufferSize = 1;
		/* 外设地址不增 */
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		/* 内存地址不增 */
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
		/* 外设数据单位 半字*/
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		/* 内存数据单位 半字*/
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		/* DMA模式：循环传输 */
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		/* 优先级：高 */
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		/* 禁止内存到内存的传输 */
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_Init(DMA1_Channel1, &DMA_InitStructure);
		
		/* 3. Enable */
		/* Enable DMA channel1 */
		DMA_Cmd(DMA1_Channel1, ENABLE);
		
		/*------------ADC1 Configuration---------------*/
		/* ADC structure*/
		/* 独立ADC模式 */
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		/* 禁止扫描模式，扫描模式用于多通道采集 */
		ADC_InitStructure.ADC_ScanConvMode = DISABLE ;
		/* 开启连续转换模式，不停地进行ADC转换 */
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		/* 不使用外部触发转换 */
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		/* 采集数据右对齐 */
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		/* 要转换的通道数目 */
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1, &ADC_InitStructure);
		
		/* clock configuration, PCLK2 DIV8, 9Hz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);
		/* 配置ADC的通道0为55.5个采样周期 */
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
		
		/* Enable configuration*/
		/* Enable ADC1 DMA*/
		ADC_DMACmd(ADC1, ENABLE);
		/* Enable ADC1 */
		ADC_Cmd(ADC1, ENABLE);
		
		/* 复位校准寄存器 */
		ADC_ResetCalibration(ADC1);
		/* 等待校准寄存器复位完成 */
		while(ADC_GetResetCalibrationStatus(ADC1));
		/* ADC校准 */
		ADC_StartCalibration(ADC1);
		/* 等待校准完成 */
		while(ADC_GetCalibrationStatus(ADC1));
		
		/* 由于没有采用外部触发，所以使用软件触发ADC转换 */
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
