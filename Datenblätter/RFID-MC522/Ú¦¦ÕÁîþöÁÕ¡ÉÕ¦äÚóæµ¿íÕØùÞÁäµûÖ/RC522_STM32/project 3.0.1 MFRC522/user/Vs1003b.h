#ifndef VS1003B_H
#define VS1003B_H  

// SPI总线速度设置 	    
#define SPI_SPEED_2   0
#define SPI_SPEED_4   1
#define SPI_SPEED_8   2
#define SPI_SPEED_16  3
#define SPI_SPEED_32  4
#define SPI_SPEED_64  5
#define SPI_SPEED_128 6
#define SPI_SPEED_256 7


#define TCS   (1<<1)  // PA1 
#define RST   (1<<4)  // PC4     			    
#define XDCS   (1<<2)  // PA2
//#define TDIN_SET(x) GPIOA->ODR=(GPIOA->ODR&~TDIN)|(x ? TDIN:0)
//#define TCLK_SET(x) GPIOA->ODR=(GPIOA->ODR&~TCLK)|(x ? TCLK:0)													    
#define TCS_SET(x)  GPIOA->ODR=(GPIOA->ODR&~TCS)|(x ? TCS:0)  
#define TRST_SET(x)  GPIOC->ODR=(GPIOC->ODR&~RST)|(x ? RST:0)  
#define TXDCS_SET(x)  GPIOA->ODR=(GPIOA->ODR&~XDCS)|(x ? XDCS:0)  

#define DREQ   (GPIOA->IDR & 0X10)//PA4

#define VS_WRITE_COMMAND 	0x02
#define VS_READ_COMMAND 	0x03		 		 

#define REG_MODE        	0x00   
#define REG_STATUS      	0x01   
#define REG_BASS        	0x02   
#define REG_CLOCKF      	0x03   
#define REG_DECODE_TIME 	0x04   
#define REG_AUDATA      	0x05   
#define REG_WRAM        	0x06   
#define REG_WRAMADDR    	0x07   
#define REG_HDAT0       	0x08   
#define REG_HDAT1       	0x09   
#define REG_AIADDR      	0x0a   
#define REG_VOL         	0x0b   
#define REG_AICTRL0     	0x0c   
#define REG_AICTRL1     	0x0d   
#define REG_AICTRL2     	0x0e   
#define REG_AICTRL3     	0x0f   

#define SM_DIFF         	0x01   
#define SM_JUMP         	0x02   
#define SM_RESET        	0x04   
#define SM_OUTOFWAV     	0x08   
#define SM_PDOWN        	0x10   
#define SM_TESTS        	0x20   
#define SM_STREAM       	0x40   
#define SM_PLUSV        	0x80   
#define SM_DACT         	0x100   
#define SM_SDIORD       	0x200   
#define SM_SDISHARE     	0x400   
#define SM_SDINEW       	0x800   
#define SM_ADPCM        	0x1000   
#define SM_ADPCM_HP     	0x2000 

//Gpio寄存器描述
//0xC017 rw 0 DDR[3:0] 设定io口方向，1是输出，0是输入
//0xC018 r 0 IDATA[3:0] 从io读出的值
//0xC019 rw 0 ODATA[3:0] 设定io值，会锁存 
#define VS_GPIO_DDR  0xC017 
#define VS_GPIO_IData  0xC018 
#define VS_GPIO_OData  0xC019 

//void Delay(__IO uint32_t nCount);

void Delay(u16 nms);
void SpiWriteByte(u8 num);
u8 SpiReadWord(void);

void Mp3Start(void);
void Mp3Reset(void);
void Mp3SetVolume(unsigned char  leftchannel,unsigned char rightchannel);
void Mp3SoftReset(void);
void Mp3WriteRegister(unsigned char addressbyte, unsigned char highbyte, unsigned char lowbyte);
unsigned int Mp3ReadRegister(unsigned char addressbyte);
void VsSineTest(void);

void  VS1003B_GPIO_DDR(unsigned char ucDDRValue);
void VS1003B_GPIO_WriteData(unsigned char ucWriteValue);
unsigned char VS1003B_GPIO_ReadData(void); 




#endif
