#include "sys.h"
#include"stm32f10x_rcc.h"
#include"stm32f10x_flash.h"
#include"stm32f10x_tim.h"
static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数


/******************************************************************************* 
说明：初始化时钟，设置为64MHz（在RC情况下的最大值） 
*******************************************************************************/
void RCC_Configuration(void)
{
    RCC_DeInit();    
    RCC_HSICmd(ENABLE);	  
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
    if(1)
    {           				    
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        FLASH_SetLatency(FLASH_Latency_2);
        RCC_HCLKConfig(RCC_SYSCLK_Div1);       
        RCC_PCLK2Config(RCC_HCLK_Div1); 	  
        RCC_PCLK1Config(RCC_HCLK_Div2);	 
        RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16); //8/2*16=64MHz
        RCC_PLLCmd(ENABLE);
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);	
        while(RCC_GetSYSCLKSource() != 0x08);
  }
}
 
//外部8M,则得到72M的系统时钟
//pll:选择的倍频数，从2开始，最大值为16 
//CHECK OK
//091209
void Stm32_Clock_Init(u8 PLL)
{
    unsigned char temp=0;   
//    MYRCC_DeInit();       //复位并配置向量表
    RCC->CR|=0x00010000;  //外部高速时钟使能HSEON
    while(!(RCC->CR>>17));//等待外部时钟就绪
    RCC->CFGR=0X00000400; //APB1/2=DIV2;AHB=DIV1;
    PLL-=2;//抵消2个单位
    RCC->CFGR|=PLL<<18;   //设置PLL值 2~16
    RCC->CFGR|=1<<16;     //PLLSRC ON 
    FLASH->ACR|=0x32;     //FLASH 2个延时周期

    RCC->CR|=0x01000000;  //PLLON
    while(!(RCC->CR>>25));//等待PLL锁定
    RCC->CFGR|=0x00000002;//PLL作为系统时钟	 
    while(temp!=0x02)     //等待PLL作为系统时钟设置成功
    {   
        temp=RCC->CFGR>>2;
        temp&=0x03;
    }    
}           


//初始化延迟函数
void delay_init(u8 SYSCLK)
{
    SysTick->CTRL&=0xfffffffb;//选择内部时钟 HCLK/8
    fac_us=SYSCLK/8;    	    
    fac_ms=(u16)fac_us*1000;
}               				    
//延时Nms
//注意Nms的范围
//Nms<=0xffffff*8/SYSCLK
//对72M条件下,Nms<=1864 
void delay_ms(u16 nms)
{             	  
    u32 temp;   	   
    SysTick->LOAD=(u32)nms*fac_ms;//时间加载
    SysTick->VAL =0x00;           //清空计数器
    SysTick->CTRL=0x01 ;          //开始倒数  
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
    SysTick->CTRL=0x00;       //关闭计数器
    SysTick->VAL =0X00;       //清空计数器          
}   
//延时us            					   
void delay_us(u32 Nus)
{   	
    u32 temp;       	 
    SysTick->LOAD=Nus*fac_us; //时间加载      		 
    SysTick->VAL=0x00;        //清空计数器
    SysTick->CTRL=0x01 ;      //开始倒数 	 
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
    SysTick->CTRL=0x00;       //关闭计数器
    SysTick->VAL =0X00;       //清空计数器	 
}



























