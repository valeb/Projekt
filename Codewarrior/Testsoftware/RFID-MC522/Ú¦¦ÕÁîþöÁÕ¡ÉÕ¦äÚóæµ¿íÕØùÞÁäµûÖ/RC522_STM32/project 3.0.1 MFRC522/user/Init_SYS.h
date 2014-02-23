#ifndef __Init_SYS_H
#define __Init_SYS_H

#include "stm32f10x.h"  //������ͷ�ļ�����ͷ�ļ���������е�һЩͷ�ļ�
#include <stdio.h>	//������׼c����������ͷ�ļ�

#define USART1_IRQ //ʹ�ܴ���1����
extern u8 USART_RX_BUF[64];     //���ջ���,���63���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 USART_RX_STA;         //����״̬���
void delay_us(u32 Nus);
void delay_ms(u32 Nus);
void NVIC_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void UART_Init(u32 pclk2,u32 bound);


#endif

