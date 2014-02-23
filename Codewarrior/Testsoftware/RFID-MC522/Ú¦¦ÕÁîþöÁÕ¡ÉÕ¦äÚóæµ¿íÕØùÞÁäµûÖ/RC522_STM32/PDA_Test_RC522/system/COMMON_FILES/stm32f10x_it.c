//#include"Delay.h"
#include "stm32f10x_it.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"		  


void NMI_Handler(void){}
void HardFault_Handler(void){ while (1) {}}
void MemManage_Handler(void){ while (1) { }}
void BusFault_Handler(void){ while (1) { }}
void UsageFault_Handler(void){  while (1) { }}
void SVC_Handler(void){}
void DebugMon_Handler(void){}
void PendSV_Handler(void){}
void SysTick_Handler(void){} 

