#ifndef _DELAY__H
#define _DELAY__H
u16 fac_us=0,fac_ms=0;
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;
	fac_us=SYSCLK/8;
	fac_ms=(u16)fac_us*1000;
}
void Delay_us(u32 tim_us)
{
	u32 tmp;
	SysTick->LOAD=tim_us*fac_us;
	SysTick->VAL=0x00;
	SysTick->CTRL=0x01;
	do
	{
		tmp=SysTick->CTRL;
	}
	while(tmp&0x01&&!(tmp&(1<<16)));
	SysTick->CTRL=0x00;
	SysTick->VAL=0x00;
}
void Delay_us1(u32 nus)
{
	u32 i,j;
	for(i=0;i<nus;i++)
	for(j=0;j<30;j++);
}
void Delay_ms(u32 tim_ms)
{
	u32 tmp;
	SysTick->LOAD=tim_ms*fac_ms;
	SysTick->VAL=0x00;
	SysTick->CTRL=0x01;
	do
	{
		tmp=SysTick->CTRL;
	}
	while(tmp&0x01&&!(tmp&(1<<16)));
	SysTick->CTRL=0x00;
	SysTick->VAL=0x00;
}

#endif
