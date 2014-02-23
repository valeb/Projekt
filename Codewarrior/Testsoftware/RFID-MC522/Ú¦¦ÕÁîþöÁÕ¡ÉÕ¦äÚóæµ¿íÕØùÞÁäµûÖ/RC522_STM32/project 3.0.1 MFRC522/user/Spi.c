#include "stm32f10x.h" //加入ST标准外设库
#include "Spi.h"       

//spi 写一个字节
u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
{
	while((SPIx->SR&0X02)==0);		//等待发送区空	  
	SPIx->DR=Byte;	 	//发送一个byte   
	while((SPIx->SR&0X01)==0);//等待接收完一个byte  
	return SPIx->DR;          	     //返回收到的数据			
}

void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet)
{
	SPIx->CR1&=0XFFC7;//Fsck=Fcpu/256
	switch(SpeedSet)
	{
		case SPI_SPEED_2://二分频
			SPIx->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz
			break;
		case SPI_SPEED_4://四分频
			SPIx->CR1|=1<<3;//Fsck=Fpclk/4=18Mhz
			break;
		case SPI_SPEED_8://八分频
			SPIx->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz
			break;
		case SPI_SPEED_16://十六分频
			SPIx->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
			break;
		case SPI_SPEED_32:  //32分频
			SPIx->CR1|=4<<3;//Fsck=Fpclk/32=2.25Mhz
			break;
		case SPI_SPEED_64:  //64分频
			SPIx->CR1|=5<<3;//Fsck=Fpclk/16=1.125Mhz
			break; 
		case SPI_SPEED_128: //128分频
			SPIx->CR1|=6<<3;//Fsck=Fpclk/16=562.5Khz
			break;
		case SPI_SPEED_256: //256分频
			SPIx->CR1|=7<<3;//Fsck=Fpclk/16=281.25Khz
			break;
	}		 
	SPIx->CR1|=1<<6; //SPI设备使能	  
} 
 

//设置SPI的速度
//SpeedSet:1,高速;0,低速;
//void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet)
//{
//	SPIx->CR1&=0XFFC7;
//	if(SpeedSet==1)//高速
//	{
//		SPIx->CR1|=0X10;//Fsck=Fpclk/2	
//	}
//	else//低速
//	{
//		SPIx->CR1|=0X20; //Fsck=Fpclk/32
//	}
//	SPIx->CR1|=1<<6; //SPI设备使能
//} 

//初始化spi1
void SPI1_Init(void) //供给vs1003b,spi flash
{
  	//SPI_InitTypeDef  SPI_InitStructure;
	//GPIO_InitTypeDef GPIO_InitStructure;
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA, ENABLE);
	RCC->APB2ENR|=1<<0;
	RCC->APB2ENR|=1<<2;

	GPIOA->CRL&=0X000FFFFF;
	GPIOA->CRL|=0XB8B00000;
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;    
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 ,ENABLE);
	RCC->APB2ENR|=1<<12;
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//	SPI_InitStructure.SPI_CRCPolynomial = 7;
//	SPI_Init(SPI1, &SPI_InitStructure);
//	
//	SPI_Cmd(SPI1, ENABLE);

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
	//SPIx_ReadWriteByte(0xff);//启动传输  
}

void SPI2_Init(void)	
{
	//SPI_InitTypeDef  SPI_InitStructure;
	//GPIO_InitTypeDef GPIO_InitStructure;
	 
	//配置SPI2管脚
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);
	RCC->APB2ENR|=1<<0;
	RCC->APB2ENR|=1<<3;

	GPIOB->CRH&=0X000FFFFF;
	GPIOB->CRH|=0XB8B00000;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;    
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
//	GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	//SPI2配置选项
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 ,ENABLE);
	RCC->APB1ENR|=1<<14;
	   
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//	SPI_InitStructure.SPI_CRCPolynomial = 7;
//	SPI_Init(SPI2, &SPI_InitStructure);
//
//	//使能SPI2
//	SPI_Cmd(SPI2, ENABLE);

	SPI2->CR1|=0<<10;//全双工模式	
	SPI2->CR1|=1<<9; //软件nss管理
	SPI2->CR1|=1<<8;  
	
	SPI2->CR1|=1<<2; //SPI主机
	SPI2->CR1|=0<<11;//8bit数据格式	
	SPI2->CR1|=1<<1; //空闲模式下SCK为1 CPOL=1
	SPI2->CR1|=1<<0; //数据采样从第二个时间边沿开始,CPHA=1  
	SPI2->CR1|=7<<3; //Fsck=Fcpu/256
	SPI2->CR1|=0<<7; //MSBfirst   
	SPI2->CR1|=1<<6; //SPI设备使能
	//SPIx_ReadWriteByte(0xff);//启动传输   
}

void SPI3_Init(void)//供给spi flash
{

	RCC->APB2ENR|=1<<0;
	AFIO->MAPR|=0X02000000;//010：关闭JTAG-DP，启用SW-DP；

	RCC->APB2ENR|=1<<3;

	GPIOB->CRL&=0XFF000FFF;
	GPIOB->CRL|=0X00B8B000; 

	//使能spi时钟
	RCC->APB1ENR|=1<<15;

	//spi1配置选项 
	SPI3->CR1|=0<<10;//全双工模式	
	SPI3->CR1|=1<<9; //软件nss管理
	SPI3->CR1|=1<<8;  
	SPI3->CR1|=1<<2; //SPI主机
	SPI3->CR1|=0<<11;//8bit数据格式	
	SPI3->CR1|=1<<1; //空闲模式下SCK为1 CPOL=1
	SPI3->CR1|=1<<0; //数据采样从第二个时间边沿开始,CPHA=1  
	SPI3->CR1|=0<<3; //Fsck=Fcpu/256	  000：Fsck=Fcpu/2

	SPI3->CR1|=0<<7; //MSBfirst   
	SPI3->CR1|=1<<6; //SPI设备使能
	//SPIx_ReadWriteByte(0xff);//启动传输  
}

////------------------------io模拟spi部分---------------------------
//// PB6-MOSI
//#define SPIv_SetData(d) { if(d & 0x80) GPIO_SetBits(GPIOB,0X0040); else GPIO_ResetBits(GPIOB,0X40);}
////PB7-MISO
//#define SPIv_ReadData() GPIO_ReadInputDataBit(GPIOB,0X80)
//// PE0-SCK
//#define SPIv_SetClk()	GPIO_SetBits(GPIOE,0X01)
//#define SPIv_ClrClk()	GPIO_ResetBits(GPIOE,0X01)
//
//u8 SPIv_WriteByte(u8 Byte)
//{
//	u8 i,Read;
//	
//	for(i=8; i; i--)
//	{	
//		SPIv_ClrClk();
//		SPIv_SetData(Byte);	
//		Byte<<=1;
//		SPIv_SetClk();
//		Read <<= 1;
//		Read |= SPIv_ReadData();
//	}
//	SPIv_ClrClk();
//	return Read;
//}
//
////用io口模拟的spi初始化
//void SPIv_Init(void)
//{
//	//GPIO_InitTypeDef GPIO_InitStructure;
//	
//	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);
//	RCC->APB2ENR|=1<<0;
//	RCC->APB2ENR|=1<<3;
//	RCC->APB2ENR|=1<<6;
//
//	GPIOB->CRL&=0X00FFFFFF;
//	GPIOB->CRL|=0XB8000000;
//	GPIOE->CRL&=0XFFFFFFF0;
//	GPIOE->CRL|=0X0000000B;
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //PB7-MISO
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
////	GPIO_Init(GPIOB, &GPIO_InitStructure);  
////
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  //PB6-MOSI
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_Init(GPIOB, &GPIO_InitStructure);
////	
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  //PE0-SCK
////	GPIO_Init(GPIOE, &GPIO_InitStructure);  
//}
