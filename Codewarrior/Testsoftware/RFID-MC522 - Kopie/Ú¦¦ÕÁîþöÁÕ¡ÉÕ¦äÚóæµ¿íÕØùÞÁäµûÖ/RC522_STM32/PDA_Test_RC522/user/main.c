#include "SYS.h" 
#include"misc.c"
#include"stm32f10x_rcc.c"
#include"stm32f10x_gpio.c"
#include"stm32f10x_flash.C"
#include"stm32f10x_tim.C"
#include "rc522.h"

unsigned char  LastKeyA[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};//NO.2卡
unsigned char  NewKeyA[6]={0x19,0x84,0x07,0x15,0x76,0x14};//NO.2卡
unsigned char  NewKey[16]={0x19,0x84,0x07,0x15,0x76,0x14,
				0xff,0x07,0x80,0x69,
				0x19,0x84,0x07,0x15,0x76,0x14};
unsigned char  Read_Data[16]={0x00};
unsigned char  Write_First_Data[16];

unsigned char  RevBuffer[30];
unsigned char  MLastSelectedSnr[4];


u8 ctrlprocess(void)
{
  signed long 	  money_value;
  float       	  f_money_value;
  unsigned char   ii,k=255;
  char            status;
  status=PcdRequest(PICC_REQIDL,&RevBuffer[0]);//寻天线区内未进入休眠状态的卡，返回卡片类型 2字节
  if(status==MI_OK)
  {
    __nop();
  }
 
  status=PcdAnticoll(&RevBuffer[2]);//防冲撞，返回卡的序列号 4字节
  if(status==MI_OK)
  {
    __nop();
  }
  memcpy(MLastSelectedSnr,&RevBuffer[2],4);
 
  status=PcdSelect(MLastSelectedSnr);//选卡
  if(status==MI_OK)
  {
    __nop();
  }
//////////////////////////////////////////////////////////////////////注册

    status=PcdAuthState(PICC_AUTHENT1A,3,LastKeyA,MLastSelectedSnr);//
    if(status==MI_OK)
    {
	__nop();
	}
	
	else   
	return 0;
	
//	status=PcdWrite(7,&NewKey[0]);
//    if(status==MI_OK)
//    {
//      __nop();
//    }
//	status=PcdAuthState(PICC_AUTHENT1A,7,NewKeyA,MLastSelectedSnr);//
//    if(status==MI_OK)
//    {
//      __nop();
//    }
    for(ii=0;ii<16;ii++)
    {
      Write_First_Data[ii]=ii;
    }
 
	do
    {
		status=PcdWrite(1,&Write_First_Data[0]);
		k--;						      
    }while(status!=MI_OK && k>0);
	    if(status==MI_OK)
    {
       __nop();
    }
    status=PcdRead(1,Read_Data);
	if(status==MI_OK)
    {
       __nop();
    }
	 
    PcdHalt();	

}  			
int  main(void) 
{	 
//   RCC_Configuration( );
     Stm32_Clock_Init(9);
	 delay_init(72);
	 InitRc522( );
     while(1)
   	 {
   		ctrlprocess( );		
	   
     }
}
