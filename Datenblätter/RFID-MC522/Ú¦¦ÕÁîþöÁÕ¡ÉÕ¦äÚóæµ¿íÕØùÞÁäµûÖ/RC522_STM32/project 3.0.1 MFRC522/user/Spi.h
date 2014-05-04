#ifndef SPI_H
#define SPI_H

// SPI总线速度设置 	    
#define SPI_SPEED_2   0
#define SPI_SPEED_4   1
#define SPI_SPEED_8   2
#define SPI_SPEED_16  3
#define SPI_SPEED_32  4
#define SPI_SPEED_64  5
#define SPI_SPEED_128 6
#define SPI_SPEED_256 7

#define SPI_ReadByte(SPIx)	SPI_WriteByte(SPIx,0)
u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 byte);
void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet);
void SPI1_Init(void);
void SPI2_Init(void);
void SPI3_Init(void);

#define SPIv_ReadByte() SPIv_WriteByte(0)
u8 SPIv_WriteByte(u8 Byte);
void SPIv_Init(void);

#endif
