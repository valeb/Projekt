#include "stm32f10x.h"	    
#include "Vs1003b.h" 
//#include "Uart.h"


unsigned char _it0=0,_it1=0,_it2=0,_it3=0,num=0;
unsigned char dw=0;
unsigned int Xs=0,Xe=0,Ys=0,Ye=0;
unsigned int X=0,Y=0;  
float X2=0,Y2=0;


unsigned char  VS_OP;
unsigned long ReadFlen;
unsigned char LVolume=2,RVolume=2;
unsigned char  BassEnhanceValue=0x00,TrebleEnhanceValue=0x00;

//延时Nms
//注意Nms的范围
//Nms<=0xffffff*8/SYSCLK
//对72M条件下,Nms<=1864 
void Delay(u16 nms)
{	 		  
	u32 temp;	

	for(;nms;nms--)
	{
		for(temp=0xfff;temp;temp--);
	}

	return;
} 
void SpiInit(void)
{

   
  //使能spi1时钟
    RCC->APB2ENR|=1<<2;       //PORTA时钟使能
	RCC->APB2ENR|=1<<4;       //PORTC时钟使能 	 
	RCC->APB2ENR|=1<<12;      //SPI1时钟使能 
	//这里只针对SPI口初始化
	GPIOA->CRL&=0X000FFFFF; 
	GPIOA->CRL|=0XBBB00000;//PA5.6.7复用 	    
	GPIOA->ODR|=0X7<<5;    //PA5.6.7上拉
		
	SPI1->CR1|=0<<10;//全双工模式	
	SPI1->CR1|=1<<9; //软件nss管理
	SPI1->CR1|=1<<8;  

	SPI1->CR1|=1<<2; //SPI主机
	SPI1->CR1|=0<<11;//8bit数据格式	
	SPI1->CR1|=1<<1; //空闲模式下SCK为1 CPOL=1
	SPI1->CR1|=1<<0; //数据采样从第二个时间边沿开始,CPHA=1  
	SPI1->CR1|=7<<3; //Fsck=Fcpu/256
	SPI1->CR1|=0<<7; //MSBfirst   
	SPI1->CR1|=1<<6; //SPI设备使能


	GPIOA->CRL&=0XFFF0F00F;		  //PA1.2.输出，4输入
	GPIOA->CRL|=0X00080330;		   //PA1:XCS  PA2:XDCS	PA4:DREQ

	GPIOC->CRL&=0XFFF0FFFF;
	GPIOC->CRL|=0X00030000;			//PC4:XREST	
	GPIOA->ODR|=(1<<4);			//vs1003 DREQ

}


u8 SPI_WriteByte(u8 Byte)
{
	u8 retry=0;
	while((SPI1->SR&1<<1)==0)		//等待发送区空	 
	{
		retry++;
		if(retry>200)return 0;
	} 
	SPI1->DR=Byte;	 	//发送一个byte   
	while((SPI1->SR&1<<0)==0)//等待接收完一个byte 
	{
		retry++;
		if(retry>200)return 0;
	} 
	return SPI1->DR;          	     //返回收到的数据			
} 

//设置SPI的速度
//SpeedSet:1,高速;0,低速;
void SPI1_SetSpeed(u8 SpeedSet)
{
	SPI1->CR1&=0XFFC7;//Fsck=Fcpu/256
	switch(SpeedSet)
	{
		case SPI_SPEED_2://二分频
			SPI1->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz
			break;
		case SPI_SPEED_4://四分频
			SPI1->CR1|=1<<3;//Fsck=Fpclk/4=18Mhz
			break;
		case SPI_SPEED_8://八分频
			SPI1->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz
			break;
		case SPI_SPEED_16://十六分频
			SPI1->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
			break;
		case SPI_SPEED_32:  //32分频
			SPI1->CR1|=4<<3;//Fsck=Fpclk/32=2.25Mhz
			break;
		case SPI_SPEED_64:  //64分频
			SPI1->CR1|=5<<3;//Fsck=Fpclk/16=1.125Mhz
			break; 
		case SPI_SPEED_128: //128分频
			SPI1->CR1|=6<<3;//Fsck=Fpclk/16=562.5Khz
			break;
		case SPI_SPEED_256: //256分频
			SPI1->CR1|=7<<3;//Fsck=Fpclk/16=281.25Khz
			break;
	}		 
	SPI1->CR1|=1<<6; //SPI设备使能	  
} 

/*************************************************************/
/*  函数名称 :  VS1003_Write_CMD                            */
/*  函数功能 ： 写vs1003寄存器                               */
/*  参数     :  寄存器地址，待写数据的高8位，待写数据的低8位 */
/*  返回值   :  无                                           */
/*-----------------------------------------------------------*/
void VS1003_Write_CMD(uint8_t addr,uint8_t hdata,uint8_t ldata)
{
	SPI1_SetSpeed(SPI_SPEED_64);//低速 
	while(DREQ==0);
	TCS_SET(0);
	SPI_WriteByte(VS_WRITE_COMMAND);
	SPI_WriteByte(addr);
	SPI_WriteByte(hdata);
	SPI_WriteByte(ldata);
	TCS_SET(1);
	//SPI1_SetSpeed(SPI_SPEED_8);//高速
}

/*************************************************************/
/*  函数名称 :  VS1003_Read_CMD                              */
/*  函数功能 ： 写vs1003寄存器                               */
/*  参数     :  寄存器地址				     				 */
/*  返回值   :  vs1003的16位寄存器的值                       */
/*-----------------------------------------------------------*/
unsigned int VS1003_Read_CMD(unsigned char addressbyte)
{
	unsigned int resultvalue = 0;
	SPI1_SetSpeed(SPI_SPEED_64);//低速 
	TXDCS_SET(1);       //xDCS =1
	TCS_SET(0);       //xCS = 0
	SPI_WriteByte(VS_READ_COMMAND); //发送读寄存器命令
	SPI_WriteByte((addressbyte));//发送寄存器的地址
	resultvalue = (unsigned int )(SPI_WriteByte(0) << 8);//读取高8位数据
	resultvalue |= SPI_WriteByte(0);  //读取低8位数据
	TCS_SET(1);       //xCS = 1        
	return resultvalue;                 //返回16位寄存器的值
}
void VS1003_Write_Data(u8 data)
{
	SPI1_SetSpeed(SPI_SPEED_8);		   //高速,对VS1003B,最大值不能超过36.864/4Mhz，这里设置为9M 
	TCS_SET(0);
	SPI_WriteByte(data);
	TCS_SET(1);
}

void Mp3Reset(void)
{	
	//SpiInit();
	TRST_SET(0);//xReset = 0   复位vs1003
	Delay(100);
	TCS_SET(1);       //xCS = 1
	TXDCS_SET(1);     //xDCS = 1
	TRST_SET(1); //xRESET = 1
//	OSTimeDly(OS_TICKS_PER_SEC/100);//延时10ms
	Delay(100);
//	while (IOPIN0 & MP3_DREQ == 0);//等待DREQ为高
	while(DREQ==0);
//    OSTimeDly(OS_TICKS_PER_SEC/10);//延时100ms 
	Delay(100);
    //Mp3SoftReset();//vs1003软复位
}

void Mp3SetVolume(unsigned char  leftchannel,unsigned char rightchannel) 
{ 
	VS1003_Write_CMD(REG_VOL,(leftchannel),(rightchannel));
}
/**********************************************************/
/*  函数名称 :  Mp3SoftReset                              */
/*  函数功能 ： vs1003软件复位                            */
/*  参数     :  无                                        */
/*  返回值   :  无                                        */
/*--------------------------------------------------------*/
void Mp3SoftReset(void)
{
	while(DREQ==0);
	SPI_WriteByte(0);//启动传输
	VS1003_Write_CMD(0, 0x08, 0x04); //软件复位
//	OSTimeDly(OS_TICKS_PER_SEC/100); //延时10ms
	Delay(10);
//	while (IOPIN0 & MP3_DREQ == 0); //等待软件复位结束
    while(DREQ==0);  //等待软件复位结束
	VS1003_Write_CMD(3, 0x98, 0x00);//设置vs1003的时钟,3倍频
	VS1003_Write_CMD (5, 0xBB, 0x81); //采样率48k，立体声
	VS1003_Write_CMD(REG_BASS, TrebleEnhanceValue, BassEnhanceValue);//设置重音
	Mp3SetVolume(LVolume,RVolume);//设置音量
//    OSTimeDly(OS_TICKS_PER_SEC/100); //延时10ms
	Delay(10);
    	
    //向vs1003发送4个字节无效数据，用以启动SPI发送
    TXDCS_SET(0);     //xDCS = 0
	SPI_WriteByte(0);
	SPI_WriteByte(0);
	SPI_WriteByte(0);
	SPI_WriteByte(0);
	TXDCS_SET(1);     //xDCS = 1
}





/***********************************************************/

//unsigned char VS1003B_Test(void) 
//{ 
//
//
//
//
////Mp3WriteRegister(0x0b,0x8f,0x8f);   //VS1003 音量     
//Mp3WriteRegister(REG_MODE,0x08,0x20);
//
//
//
//TCS_SET(1);       //xCS = 1
//TXDCS_SET(0);
//
//SpiWriteByte(0x53);    
//SpiWriteByte(0xef);    
//SpiWriteByte(0x6e);    
//SpiWriteByte(0x24);    
//SpiWriteByte(0x00);    
//SpiWriteByte(0x00); 
//SpiWriteByte(0x00); 
//SpiWriteByte(0x00); 
//Mp3WriteRegister(0x0b,0x7f,0x7f);   //VS1003 音?
//Delay(200); 
//
//    #if 0
//    SpiWriteByte(0x45); 
//    SpiWriteByte(0x78); 
//SpiWriteByte(0x69); 
//SpiWriteByte(0x74); 
//SpiWriteByte(0x00); 
//SpiWriteByte(0x00); 
//SpiWriteByte(0x00); 
//SpiWriteByte(0x00); 
//    #endif
//
////TXDCS_SET(1); 
////SPI_SetSpeedHigh(); 
//     
//    return 0; 
//} 

/*---------------------------------------------------------*/
void Mp3Start(void)
{	
	SpiInit();
	
	TRST_SET(0);//xReset = 0   复位vs1003();
	
	Delay(10);       
	SPI_WriteByte(0xff);//发送一个字节的无效数据，启动SPI传输
	TXDCS_SET(1);       //xDCS =1
	TCS_SET(1);       //xCS = 1
	TRST_SET(1);//xReset =1   
	Delay(10);      

	//VS1003B_GPIO_DDR(0x0c);//gpio 控制led
	//VS1003B_GPIO_WriteData(0x0c);//点亮io2和io3
	while(DREQ==0);
	
	VS1003_Write_CMD(REG_MODE,0x08,0x00);//进入vs1003的播放模式
	Delay(10);             
	VS1003_Write_CMD(3,0x60,0x00);//VS1003 倍时钟
	Delay(10);             
	VS1003_Write_CMD(0x0b,0x2f,0x2f);   //VS1003 音量
	Delay(10);         
    while(DREQ==0);	 
 }
/***********************************************************/
/*  函数名称 :  VsSineTest                                 */
/*  函数功能 ： vs1003正弦测试，将该函数放在while循环中，  */
/*              如果能持续听到一高一低的声音，证明测试通过 */                            
/*  参数     :  无                                         */
/*  返回值   :  无                                         */
/*---------------------------------------------------------*/
void VsSineTest(void)
{
	TRST_SET(0);//xReset = 0   复位vs1003(); 
//	OSTimeDly(OS_TICKS_PER_SEC/10);   //延时100ms 
	Delay(10);       
	SPI_WriteByte(0xff);//发送一个字节的无效数据，启动SPI传输
	TXDCS_SET(1);       //xDCS =1
	TCS_SET(1);       //xCS = 1
	TRST_SET(1);//xReset =1   
//	OSTimeDly(OS_TICKS_PER_SEC/10);  
	Delay(10);             
 	VS1003_Write_CMD(REG_MODE,0x08,0x20);//进入vs1003的测试模式
	//VS1003_Write_CMD(REG_MODE,0x08,0x00);//进入vs1003的播放模式
//	while (IO0PIN & MP3_DREQ == 0);     //等待DREQ为高
	while(DREQ==0);
 	TXDCS_SET(0);       //     //xDCS = 0，选择vs1003的数据接口
 	
 	//向vs1003发送正弦测试命令：0x53 0xef 0x6e n 0x00 0x00 0x00 0x00
 	//其中n = 0x24, 设定vs1003所产生的正弦波的频率值，具体计算方法见vs1003的datasheet
    SPI_WriteByte(0x53);      
	SPI_WriteByte(0xef);      
	SPI_WriteByte(0x6e);      
	SPI_WriteByte(0x24);      
	SPI_WriteByte(0x00);      
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
//	OSTimeDly(OS_TICKS_PER_SEC/2);
	Delay(500);
	TXDCS_SET(1);    //程序执行到这里后应该能从个单一频率的声音
  	
    //退出正弦测试				 
	TXDCS_SET(0);    
	SPI_WriteByte(0x45);
	SPI_WriteByte(0x78);
	SPI_WriteByte(0x69);
	SPI_WriteByte(0x74);
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
//	OSTimeDly(OS_TICKS_PER_SEC/2);
	Delay(500);
	TXDCS_SET(1);    

    //再次进入正弦测试并设置n值为0x44，即将正弦波的频率设置为另外的值
    TXDCS_SET(0);    
	SPI_WriteByte(0x53);      
	SPI_WriteByte(0xef);      
	SPI_WriteByte(0x6e);      
	SPI_WriteByte(0x44);      
	SPI_WriteByte(0x00);      
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
//	OSTimeDly(OS_TICKS_PER_SEC/2);
	Delay(500);
	TXDCS_SET(1);    

	//退出正弦测试
	TXDCS_SET(0);    
	SPI_WriteByte(0x45);
	SPI_WriteByte(0x78);
	SPI_WriteByte(0x69);
	SPI_WriteByte(0x74);
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
//	OSTimeDly(OS_TICKS_PER_SEC/2);
	Delay(500);
	TXDCS_SET(1);    
 }
//
////GPIO部分
////写寄存器，参数，地址和数据 
//void VS1003B_WriteCMD(unsigned char addr, unsigned int dat) 
//{ 
//	Mp3WriteRegister(addr,dat>>8,dat); 
//} 
//
////读寄存器，参数 地址 返回内容 
//unsigned int VS1003B_ReadCMD(unsigned char addr) 
//{ 
//	return(Mp3ReadRegister(addr)); 
//} 
//
//void  VS1003B_GPIO_DDR(unsigned char ucDDRValue) 
//{ 
//	VS1003B_WriteCMD(REG_WRAMADDR,VS_GPIO_DDR); 
//	VS1003B_WriteCMD(REG_WRAM,ucDDRValue); 
//} 
//
//void VS1003B_GPIO_WriteData(unsigned char ucWriteValue) 
//{ 
//	VS1003B_WriteCMD(REG_WRAMADDR,VS_GPIO_OData); 
//	VS1003B_WriteCMD(REG_WRAM,ucWriteValue); 
//} 
//
//unsigned char VS1003B_GPIO_ReadData(void) 
//{ 
//	unsigned char ucReadValue; 
//
//	VS1003B_WriteCMD(REG_WRAMADDR,VS_GPIO_IData); 
//	ucReadValue = VS1003B_ReadCMD(REG_WRAM); 
//	return(ucReadValue);
//} 
