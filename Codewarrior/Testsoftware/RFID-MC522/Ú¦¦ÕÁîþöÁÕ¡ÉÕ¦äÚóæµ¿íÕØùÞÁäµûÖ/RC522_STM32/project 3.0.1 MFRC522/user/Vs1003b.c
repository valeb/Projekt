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

//��ʱNms
//ע��Nms�ķ�Χ
//Nms<=0xffffff*8/SYSCLK
//��72M������,Nms<=1864 
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

   
  //ʹ��spi1ʱ��
    RCC->APB2ENR|=1<<2;       //PORTAʱ��ʹ��
	RCC->APB2ENR|=1<<4;       //PORTCʱ��ʹ�� 	 
	RCC->APB2ENR|=1<<12;      //SPI1ʱ��ʹ�� 
	//����ֻ���SPI�ڳ�ʼ��
	GPIOA->CRL&=0X000FFFFF; 
	GPIOA->CRL|=0XBBB00000;//PA5.6.7���� 	    
	GPIOA->ODR|=0X7<<5;    //PA5.6.7����
		
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


	GPIOA->CRL&=0XFFF0F00F;		  //PA1.2.�����4����
	GPIOA->CRL|=0X00080330;		   //PA1:XCS  PA2:XDCS	PA4:DREQ

	GPIOC->CRL&=0XFFF0FFFF;
	GPIOC->CRL|=0X00030000;			//PC4:XREST	
	GPIOA->ODR|=(1<<4);			//vs1003 DREQ

}


u8 SPI_WriteByte(u8 Byte)
{
	u8 retry=0;
	while((SPI1->SR&1<<1)==0)		//�ȴ���������	 
	{
		retry++;
		if(retry>200)return 0;
	} 
	SPI1->DR=Byte;	 	//����һ��byte   
	while((SPI1->SR&1<<0)==0)//�ȴ�������һ��byte 
	{
		retry++;
		if(retry>200)return 0;
	} 
	return SPI1->DR;          	     //�����յ�������			
} 

//����SPI���ٶ�
//SpeedSet:1,����;0,����;
void SPI1_SetSpeed(u8 SpeedSet)
{
	SPI1->CR1&=0XFFC7;//Fsck=Fcpu/256
	switch(SpeedSet)
	{
		case SPI_SPEED_2://����Ƶ
			SPI1->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz
			break;
		case SPI_SPEED_4://�ķ�Ƶ
			SPI1->CR1|=1<<3;//Fsck=Fpclk/4=18Mhz
			break;
		case SPI_SPEED_8://�˷�Ƶ
			SPI1->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz
			break;
		case SPI_SPEED_16://ʮ����Ƶ
			SPI1->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
			break;
		case SPI_SPEED_32:  //32��Ƶ
			SPI1->CR1|=4<<3;//Fsck=Fpclk/32=2.25Mhz
			break;
		case SPI_SPEED_64:  //64��Ƶ
			SPI1->CR1|=5<<3;//Fsck=Fpclk/16=1.125Mhz
			break; 
		case SPI_SPEED_128: //128��Ƶ
			SPI1->CR1|=6<<3;//Fsck=Fpclk/16=562.5Khz
			break;
		case SPI_SPEED_256: //256��Ƶ
			SPI1->CR1|=7<<3;//Fsck=Fpclk/16=281.25Khz
			break;
	}		 
	SPI1->CR1|=1<<6; //SPI�豸ʹ��	  
} 

/*************************************************************/
/*  �������� :  VS1003_Write_CMD                            */
/*  �������� �� дvs1003�Ĵ���                               */
/*  ����     :  �Ĵ�����ַ����д���ݵĸ�8λ����д���ݵĵ�8λ */
/*  ����ֵ   :  ��                                           */
/*-----------------------------------------------------------*/
void VS1003_Write_CMD(uint8_t addr,uint8_t hdata,uint8_t ldata)
{
	SPI1_SetSpeed(SPI_SPEED_64);//���� 
	while(DREQ==0);
	TCS_SET(0);
	SPI_WriteByte(VS_WRITE_COMMAND);
	SPI_WriteByte(addr);
	SPI_WriteByte(hdata);
	SPI_WriteByte(ldata);
	TCS_SET(1);
	//SPI1_SetSpeed(SPI_SPEED_8);//����
}

/*************************************************************/
/*  �������� :  VS1003_Read_CMD                              */
/*  �������� �� дvs1003�Ĵ���                               */
/*  ����     :  �Ĵ�����ַ				     				 */
/*  ����ֵ   :  vs1003��16λ�Ĵ�����ֵ                       */
/*-----------------------------------------------------------*/
unsigned int VS1003_Read_CMD(unsigned char addressbyte)
{
	unsigned int resultvalue = 0;
	SPI1_SetSpeed(SPI_SPEED_64);//���� 
	TXDCS_SET(1);       //xDCS =1
	TCS_SET(0);       //xCS = 0
	SPI_WriteByte(VS_READ_COMMAND); //���Ͷ��Ĵ�������
	SPI_WriteByte((addressbyte));//���ͼĴ����ĵ�ַ
	resultvalue = (unsigned int )(SPI_WriteByte(0) << 8);//��ȡ��8λ����
	resultvalue |= SPI_WriteByte(0);  //��ȡ��8λ����
	TCS_SET(1);       //xCS = 1        
	return resultvalue;                 //����16λ�Ĵ�����ֵ
}
void VS1003_Write_Data(u8 data)
{
	SPI1_SetSpeed(SPI_SPEED_8);		   //����,��VS1003B,���ֵ���ܳ���36.864/4Mhz����������Ϊ9M 
	TCS_SET(0);
	SPI_WriteByte(data);
	TCS_SET(1);
}

void Mp3Reset(void)
{	
	//SpiInit();
	TRST_SET(0);//xReset = 0   ��λvs1003
	Delay(100);
	TCS_SET(1);       //xCS = 1
	TXDCS_SET(1);     //xDCS = 1
	TRST_SET(1); //xRESET = 1
//	OSTimeDly(OS_TICKS_PER_SEC/100);//��ʱ10ms
	Delay(100);
//	while (IOPIN0 & MP3_DREQ == 0);//�ȴ�DREQΪ��
	while(DREQ==0);
//    OSTimeDly(OS_TICKS_PER_SEC/10);//��ʱ100ms 
	Delay(100);
    //Mp3SoftReset();//vs1003��λ
}

void Mp3SetVolume(unsigned char  leftchannel,unsigned char rightchannel) 
{ 
	VS1003_Write_CMD(REG_VOL,(leftchannel),(rightchannel));
}
/**********************************************************/
/*  �������� :  Mp3SoftReset                              */
/*  �������� �� vs1003�����λ                            */
/*  ����     :  ��                                        */
/*  ����ֵ   :  ��                                        */
/*--------------------------------------------------------*/
void Mp3SoftReset(void)
{
	while(DREQ==0);
	SPI_WriteByte(0);//��������
	VS1003_Write_CMD(0, 0x08, 0x04); //�����λ
//	OSTimeDly(OS_TICKS_PER_SEC/100); //��ʱ10ms
	Delay(10);
//	while (IOPIN0 & MP3_DREQ == 0); //�ȴ������λ����
    while(DREQ==0);  //�ȴ������λ����
	VS1003_Write_CMD(3, 0x98, 0x00);//����vs1003��ʱ��,3��Ƶ
	VS1003_Write_CMD (5, 0xBB, 0x81); //������48k��������
	VS1003_Write_CMD(REG_BASS, TrebleEnhanceValue, BassEnhanceValue);//��������
	Mp3SetVolume(LVolume,RVolume);//��������
//    OSTimeDly(OS_TICKS_PER_SEC/100); //��ʱ10ms
	Delay(10);
    	
    //��vs1003����4���ֽ���Ч���ݣ���������SPI����
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
////Mp3WriteRegister(0x0b,0x8f,0x8f);   //VS1003 ����     
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
//Mp3WriteRegister(0x0b,0x7f,0x7f);   //VS1003 ��?
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
	
	TRST_SET(0);//xReset = 0   ��λvs1003();
	
	Delay(10);       
	SPI_WriteByte(0xff);//����һ���ֽڵ���Ч���ݣ�����SPI����
	TXDCS_SET(1);       //xDCS =1
	TCS_SET(1);       //xCS = 1
	TRST_SET(1);//xReset =1   
	Delay(10);      

	//VS1003B_GPIO_DDR(0x0c);//gpio ����led
	//VS1003B_GPIO_WriteData(0x0c);//����io2��io3
	while(DREQ==0);
	
	VS1003_Write_CMD(REG_MODE,0x08,0x00);//����vs1003�Ĳ���ģʽ
	Delay(10);             
	VS1003_Write_CMD(3,0x60,0x00);//VS1003 ��ʱ��
	Delay(10);             
	VS1003_Write_CMD(0x0b,0x2f,0x2f);   //VS1003 ����
	Delay(10);         
    while(DREQ==0);	 
 }
/***********************************************************/
/*  �������� :  VsSineTest                                 */
/*  �������� �� vs1003���Ҳ��ԣ����ú�������whileѭ���У�  */
/*              ����ܳ�������һ��һ�͵�������֤������ͨ�� */                            
/*  ����     :  ��                                         */
/*  ����ֵ   :  ��                                         */
/*---------------------------------------------------------*/
void VsSineTest(void)
{
	TRST_SET(0);//xReset = 0   ��λvs1003(); 
//	OSTimeDly(OS_TICKS_PER_SEC/10);   //��ʱ100ms 
	Delay(10);       
	SPI_WriteByte(0xff);//����һ���ֽڵ���Ч���ݣ�����SPI����
	TXDCS_SET(1);       //xDCS =1
	TCS_SET(1);       //xCS = 1
	TRST_SET(1);//xReset =1   
//	OSTimeDly(OS_TICKS_PER_SEC/10);  
	Delay(10);             
 	VS1003_Write_CMD(REG_MODE,0x08,0x20);//����vs1003�Ĳ���ģʽ
	//VS1003_Write_CMD(REG_MODE,0x08,0x00);//����vs1003�Ĳ���ģʽ
//	while (IO0PIN & MP3_DREQ == 0);     //�ȴ�DREQΪ��
	while(DREQ==0);
 	TXDCS_SET(0);       //     //xDCS = 0��ѡ��vs1003�����ݽӿ�
 	
 	//��vs1003�������Ҳ������0x53 0xef 0x6e n 0x00 0x00 0x00 0x00
 	//����n = 0x24, �趨vs1003�����������Ҳ���Ƶ��ֵ��������㷽����vs1003��datasheet
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
	TXDCS_SET(1);    //����ִ�е������Ӧ���ܴӸ���һƵ�ʵ�����
  	
    //�˳����Ҳ���				 
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

    //�ٴν������Ҳ��Բ�����nֵΪ0x44���������Ҳ���Ƶ������Ϊ�����ֵ
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

	//�˳����Ҳ���
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
////GPIO����
////д�Ĵ�������������ַ������ 
//void VS1003B_WriteCMD(unsigned char addr, unsigned int dat) 
//{ 
//	Mp3WriteRegister(addr,dat>>8,dat); 
//} 
//
////���Ĵ��������� ��ַ �������� 
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
