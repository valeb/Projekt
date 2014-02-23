#ifndef __Init_SYS_H
#define __Init_SYS_H

#include "stm32f10x.h"  //包含的头文件，此头文件会包含库中的一些头文件
#include <stdio.h>	//包含标准c库的输入输出头文件

#define USART1_IRQ //使能串口1接收
extern u8 USART_RX_BUF[64];     //接收缓冲,最大63个字节.末字节为换行符 
extern u8 USART_RX_STA;         //接收状态标记
void delay_us(u32 Nus);
void delay_ms(u32 Nus);
void NVIC_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void UART_Init(u32 pclk2,u32 bound);


#endif

