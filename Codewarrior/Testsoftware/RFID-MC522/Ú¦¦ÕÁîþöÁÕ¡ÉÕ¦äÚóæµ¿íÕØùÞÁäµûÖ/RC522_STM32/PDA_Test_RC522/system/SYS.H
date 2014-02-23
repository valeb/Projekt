#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"
void Stm32_Clock_Init(u8 PLL);  // ±÷”≥ı ºªØ  
void RCC_Configuration(void);	
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 Nus);


#endif











