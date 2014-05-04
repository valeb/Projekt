#include "include.h"

uchar data NewKey[16]={0x00,0x00,0x00,0x00,0x00,0x00,
		0xff,0x07,0x80,0x69,
		0x00,0x00,0x00,0x00,0x00,0x00};
				
unsigned char idata Read_Data[16]={0x00};
uchar idata PassWd[6]={0x00};
uchar idata WriteData[16];
unsigned char idata RevBuffer[30];
unsigned char data MLastSelectedSnr[4];

uchar uart_count,uart_comp;

uint data KeyNum,KuaiN;
uchar data bWarn,bPass;
uchar data KeyTime,WaitTimes,SysTime;
uchar data oprationcard,bSendID;

extern char PcdReset(void);
extern char PcdRequest(unsigned char req_code,unsigned char *pTagType);
extern void PcdAntennaOn(void);
extern void PcdAntennaOff(void);
extern char M500PcdConfigISOType(unsigned char type);
extern char PcdAnticoll(unsigned char *pSnr);
extern char PcdSelect(unsigned char *pSnr);
extern char PcdAuthState(unsigned char auth_mode,unsigned char addr,unsigned char *pKey,unsigned char *pSnr);
extern char PcdWrite(unsigned char addr,unsigned char *pData);
extern char PcdRead(unsigned char addr,unsigned char *pData);
extern char PcdHalt(void);

extern uchar GetKey(void);

void delay_ms(uint data tms)
{
  uint data ii;
  while(tms)
  {
    tms--;
    for(ii=0;ii<400;ii++)
    {
      nop();nop();nop();nop();nop();nop();
    }
  }
}

void Warn(void)
{
  uchar data ii;
  for(ii=0;ii<3;ii++)
  {
    SET_BEEP;
    delay_ms(120);
    CLR_BEEP;
    delay_ms(120);
  }
}

void Pass(void)
{
  SET_BEEP;
  delay_ms(700);
  CLR_BEEP;
}

void InitPort(void)
{
  P0M1=0x00;
  P0M0=0xff;
  
  P1M1=0x00;
  P1M0=0x00;
  
  P24=1;
  P2M1=0x10;
  P2M0=0x88;
  
  P30=1;
  P36=1;
  P3M1=0x41;
  P3M0=0xa2;
  
  P41=1;
  P4M1=0x02;
  P4M0=0x04;
  
}

/**********************************************************************
functionName:putChar(BYTE sentData)
description:通过串口发送数据sentData
**********************************************************************/
void sendchar1(uchar data sentData)
{
  ES=0;
  TI=0;
  SBUF=sentData;
  while(TI==0);
  TI=0;
  ES=1;
}

//UART0 initialize
// desired baud rate: 9600
// actual: baud rate:9600 (0.0%)
// char size: 8 bit
// parity: Disabled
void uart_init(void)
{
  SCON = 0x50;
  BRT=RELOAD_COUNT;
  AUXR=0x11;
  AUXR1=0x00;  //0x80:p1  0x00:p3
  ES=1;
}

void uart_interrupt_receive(void) interrupt 4
{
  uchar data R_Char;
  if(RI==1);
  {
    RI=0;
    WaitTimes=0;
    R_Char=SBUF;
    RevBuffer[uart_count]=R_Char;
    uart_count++;
    if(uart_count==RevBuffer[0])
    {
      uart_comp=1;
    } 
  } 
}

void InitRc522(void)
{
  PcdReset();
  PcdAntennaOff();  
  PcdAntennaOn();
  M500PcdConfigISOType( 'A' );
}

//TIMER1 initialize - prescale:8
// desired value: 20mSec
// actual value: 19.999mSec (0.0%)
void init_time0(void)  //25ms
{
  TMOD=0x01;
  TH0=0x79;
  TL0=0xfe;
  ET0=1;
  TR0=1;
}

void  time0_routine(void) interrupt 1
{
  //TIMER1 has overflowed
  TMOD=0x01;
  TH0=0x69;
  TL0=0xfe;
  WaitTimes++;
  SysTime++;
  if(WaitTimes>=10)
  {
    WaitTimes=10;
    uart_count=0;
    uart_comp=0;
  }
  if(KeyTime)
  {
    KeyTime--;
  }
}

void InitAll(void)
{
  InitPort();
  InitRc522();
  EA=0;
  init_time0();
  uart_init();
  EA=1; //re-enable interrupts  
  bWarn=0;
  bPass=0;
  SysTime=0;
  KeyTime=0;
  WaitTimes=0;
  KeyNum=0;
  KuaiN=0;
  oprationcard=0;
  uart_count=0;
  uart_comp=0;
  bSendID=0;
  Pass();
}

void ctrlprocess(void)
{
  unsigned char data ii;
  char data status;
  
  PcdReset();
  status=PcdRequest(PICC_REQIDL,&RevBuffer[0]);//寻天线区内未进入休眠状态的卡，返回卡片类型 2字节
  if(status!=MI_OK)
  {
    return;
  }
  status=PcdAnticoll(&RevBuffer[2]);//防冲撞，返回卡的序列号 4字节
  if(status!=MI_OK)
  {
    return;
  }
  memcpy(MLastSelectedSnr,&RevBuffer[2],4); 
  status=PcdSelect(MLastSelectedSnr);//选卡
  if(status!=MI_OK)
  {
    return;
  }
  if(oprationcard==KEYCARD)//修改密码
  {
    oprationcard=0;    
    status=PcdAuthState(PICC_AUTHENT1A,KuaiN,PassWd,MLastSelectedSnr);//
    if(status!=MI_OK)
    {
      bWarn=1;
      return;
    }
    status=PcdWrite(KuaiN,&NewKey[0]);
    if(status!=MI_OK)
    {
      bWarn=1;
      return;
    }
    bPass=1;
    PcdHalt();		
  }
  else if(oprationcard==READCARD)//读卡
  {
    oprationcard=0;
    status=PcdAuthState(PICC_AUTHENT1A,KuaiN,PassWd,MLastSelectedSnr);//
    if(status!=MI_OK)
    {
      bWarn=1;
      return;
    }
    status=PcdRead(KuaiN,Read_Data);
    if(status!=MI_OK)
    {
      bWarn=1;
      return;
    }
    for(ii=0;ii<16;ii++)
    {
      sendchar1(Read_Data[ii]);
    }
    bPass=1;
    PcdHalt();	
  }
  else if(oprationcard==WRITECARD)//写卡
  {
    oprationcard=0;
    status=PcdAuthState(PICC_AUTHENT1A,KuaiN,PassWd,MLastSelectedSnr);//
    if(status!=MI_OK)
    {
      bWarn=1;
      return;
    }
    status=PcdWrite(KuaiN,&WriteData[0]);
    if(status!=MI_OK)
    {
      bWarn=1;
      return;
    }	
    bPass=1;
    PcdHalt();	
  } 
  else if(oprationcard==SENDID)//发送卡号
  {
    oprationcard=0;
    for(ii=0;ii<4;ii++)
    {
    	sendchar1(MLastSelectedSnr[ii]);
    }
    bPass=1;
  }       					
}

void ctrl_uart(void)
{
  uchar ii;
  switch(RevBuffer[1])
  {
    case 0xa0:
      oprationcard=SENDID;
      break;
    case 0xa1://读数据
      oprationcard=READCARD;
      for(ii=0;ii<6;ii++)
      {
        PassWd[ii]=RevBuffer[ii+2];
      } 
      KuaiN=RevBuffer[8];
      break;
    case 0xa2://写数据
      oprationcard=WRITECARD;
      for(ii=0;ii<6;ii++)
      {
        PassWd[ii]=RevBuffer[ii+2];
      } 
      KuaiN=RevBuffer[8];
      for(ii=0;ii<16;ii++)
      {
        WriteData[ii]=RevBuffer[ii+9];
      }
      break;  
    case 0xa3:
      oprationcard=KEYCARD; 
      for(ii=0;ii<6;ii++)
      {
        PassWd[ii]=RevBuffer[ii+2];
      } 
      KuaiN=RevBuffer[8];
      for(ii=0;ii<6;ii++)
      {
        NewKey[ii]=RevBuffer[ii+9];
        NewKey[ii+10]=RevBuffer[ii+9];
      }
      break;
    default:
      break;                     
  }
  uart_comp=0;
  uart_count=0;
}

void main(void)
{
  InitAll();
  while(1)
  {
    KeyNum=GetKey();   
    if(KeyNum==N_1)
    {
      KeyTime=15;
      sendchar1(0xaa);
      oprationcard=SENDID;
    }
    if(bWarn)
    {
      bWarn=0;
      Warn();
    }
    if(bPass)
    {
      bPass=0;
      Pass();
    }
    if(uart_comp)
    {
      ctrl_uart();     
    }
    if(SysTime>=2)
    {
      SysTime=0;
      ctrlprocess();
    }
  }  
}