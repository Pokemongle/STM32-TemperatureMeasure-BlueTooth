#ifndef __USART1_H
#define __USART1_H
/* include */
#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

/* define */
#define USART1_DR_Base 0x40013804
#define SENDBUFF_SIZE 5000

/* function */
void DMA_Config(void);
int fputc(int ch, FILE* f);
static char* itoa(int value, char *string, int radix);
static void NVIC_Config(void);
void USART1_Init(void);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);

#endif
