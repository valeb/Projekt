#include "stm32f10x.h" //����ST��׼�����
#include "Spi.h"       

//spi дһ���ֽ�
u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
{
	while((SPIx->SR&0X02)==0);		//�ȴ���������	  
	SPIx->DR=Byte;	 	//����һ��byte   
	while((SPIx->SR&0X01)==0);//�ȴ�������һ��byte  
	return SPIx->DR;          	     //�����յ�������			
}

void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet)
{
	SPIx->CR1&=0XFFC7;//Fsck=Fcpu/256
	switch(SpeedSet)
	{
		case SPI_SPEED_2://����Ƶ
			SPIx->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz
			break;
		case SPI_SPEED_4://�ķ�Ƶ
			SPIx->CR1|=1<<3;//Fsck=Fpclk/4=18Mhz
			break;
		case SPI_SPEED_8://�˷�Ƶ
			SPIx->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz
			break;
		case SPI_SPEED_16://ʮ����Ƶ
			SPIx->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
			break;
		case SPI_SPEED_32:  //32��Ƶ
			SPIx->CR1|=4<<3;//Fsck=Fpclk/32=2.25Mhz
			break;
		case SPI_SPEED_64:  //64��Ƶ
			SPIx->CR1|=5<<3;//Fsck=Fpclk/16=1.125Mhz
			break; 
		case SPI_SPEED_128: //128��Ƶ
			SPIx->CR1|=6<<3;//Fsck=Fpclk/16=562.5Khz
			break;
		case SPI_SPEED_256: //256��Ƶ
			SPIx->CR1|=7<<3;//Fsck=Fpclk/16=281.25Khz
			break;
	}		 
	SPIx->CR1|=1<<6; //SPI�豸ʹ��	  
} 
 

//����SPI���ٶ�
//SpeedSet:1,����;0,����;
//void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet)
//{
//	SPIx->CR1&=0XFFC7;
//	if(SpeedSet==1)//����
//	{
//		SPIx->CR1|=0X10;//Fsck=Fpclk/2	
//	}
//	else//����
//	{
//		SPIx->CR1|=0X20; //Fsck=Fpclk/32
//	}
//	SPIx->CR1|=1<<6; //SPI�豸ʹ��
//} 

//��ʼ��spi1
void SPI1_Init(void) //����vs1003b,spi flash
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

	SPI1->CR1|=0<<10;//ȫ˫��ģʽ	
	SPI1->CR1|=1<<9; //���nss����
	SPI1->CR1|=1<<8;  

	SPI1->CR1|=1<<2; //SPI����
	SPI1->CR1|=0<<11;//8bit���ݸ�ʽ	
	SPI1->CR1|=1<<1; //����ģʽ��SCKΪ1 CPOL=1
	SPI1->CR1|=1<<0; //���ݲ����ӵڶ���ʱ����ؿ�ʼ,CPHA=1  
	SPI1->CR1|=7<<3; //Fsck=Fcpu/256
	SPI1->CR1|=0<<7; //MSBfirst   
	SPI1->CR1|=1<<6; //SPI�豸ʹ��
	//SPIx_ReadWriteByte(0xff);//��������  
}

void SPI2_Init(void)	
{
	//SPI_InitTypeDef  SPI_InitStructure;
	//GPIO_InitTypeDef GPIO_InitStructure;
	 
	//����SPI2�ܽ�
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
	
	//SPI2����ѡ��
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
//	//ʹ��SPI2
//	SPI_Cmd(SPI2, ENABLE);

	SPI2->CR1|=0<<10;//ȫ˫��ģʽ	
	SPI2->CR1|=1<<9; //���nss����
	SPI2->CR1|=1<<8;  
	
	SPI2->CR1|=1<<2; //SPI����
	SPI2->CR1|=0<<11;//8bit���ݸ�ʽ	
	SPI2->CR1|=1<<1; //����ģʽ��SCKΪ1 CPOL=1
	SPI2->CR1|=1<<0; //���ݲ����ӵڶ���ʱ����ؿ�ʼ,CPHA=1  
	SPI2->CR1|=7<<3; //Fsck=Fcpu/256
	SPI2->CR1|=0<<7; //MSBfirst   
	SPI2->CR1|=1<<6; //SPI�豸ʹ��
	//SPIx_ReadWriteByte(0xff);//��������   
}

void SPI3_Init(void)//����spi flash
{

	RCC->APB2ENR|=1<<0;
	AFIO->MAPR|=0X02000000;//010���ر�JTAG-DP������SW-DP��

	RCC->APB2ENR|=1<<3;

	GPIOB->CRL&=0XFF000FFF;
	GPIOB->CRL|=0X00B8B000; 

	//ʹ��spiʱ��
	RCC->APB1ENR|=1<<15;

	//spi1����ѡ�� 
	SPI3->CR1|=0<<10;//ȫ˫��ģʽ	
	SPI3->CR1|=1<<9; //���nss����
	SPI3->CR1|=1<<8;  
	SPI3->CR1|=1<<2; //SPI����
	SPI3->CR1|=0<<11;//8bit���ݸ�ʽ	
	SPI3->CR1|=1<<1; //����ģʽ��SCKΪ1 CPOL=1
	SPI3->CR1|=1<<0; //���ݲ����ӵڶ���ʱ����ؿ�ʼ,CPHA=1  
	SPI3->CR1|=0<<3; //Fsck=Fcpu/256	  000��Fsck=Fcpu/2

	SPI3->CR1|=0<<7; //MSBfirst   
	SPI3->CR1|=1<<6; //SPI�豸ʹ��
	//SPIx_ReadWriteByte(0xff);//��������  
}

////------------------------ioģ��spi����---------------------------
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
////��io��ģ���spi��ʼ��
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
