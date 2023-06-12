#include "stm32f10x.h"
#include "usart1.h"
#include "delay.h"

int main(void){
		USART1_Config();
		
		printf("\r\n 大学生哪有不疯的，硬撑罢了！ \r\n");
		printf("\r\n Welcome:) \r\n");
		USART1_printf(USART1, "\r\n This is a USART1_printf demo \r\n");
		USART1_printf(USART1, "\r\n ("__DATE__ " - " __TIME__ ") \r\n");
		while(1);
}
