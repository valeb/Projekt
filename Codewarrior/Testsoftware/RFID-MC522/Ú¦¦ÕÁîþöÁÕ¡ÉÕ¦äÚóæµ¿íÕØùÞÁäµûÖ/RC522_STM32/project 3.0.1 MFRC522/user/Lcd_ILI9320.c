/********************************************************************************
 * FileName:       
 * Author:         
 * Description:    
 * Version:        
 * Function List:  
*******************************************************************************/
#include "Lcd.h"
#include "Lcd_font.h"
//#include "SpiFlash.h" 


#define Bank1_LCD_R    ((uint32_t)0x60000000)    //disp Reg ADDR
#define Bank1_LCD_D    ((uint32_t)0x60020000)	//disp Data ADDR 

//9320功能寄存器地址
#define WINDOW_XADDR_START	0x0050 // 水平的开始地址组
#define WINDOW_XADDR_END		0x0051 // 水平的结束地址组
#define WINDOW_YADDR_START	0x0052 // 垂直的开始地址组
#define WINDOW_YADDR_END		0x0053 // 垂直的结束地址组
#define GRAM_XADDR		    		0x0020 // GRAM 水平的地址组
#define GRAM_YADDR		    		0x0021 // GRAM 垂直的地址组
#define GRAMWR 			    			0x0022 // GRAM

/**********************************************
函数名：LCD_Delay
功能：用于LCD配置延时
入口参数：延时数
返回值：无
***********************************************/
static void LCD_DelayMs(u32 Ms)
{
  u32 i;
	for(; Ms; Ms--)
		for(i=1000;i;i--);
}

/*************************************************
函数名：LCD_WR_Cmd
功能：传入寄存器地址
入口参数：寄存器地址
返回值：无
*************************************************/
static void LCD_WriteIndex(u16 index)
{
	*(__IO uint16_t *) (Bank1_LCD_R)= index;	
}

/*************************************************
函数名：LCD_WR_Reg
功能：对lcd寄存器，写命令
入口参数：寄存器地址和命令
返回值：寄存器值
*************************************************/
static void LCD_WriteReg(u16 index,u16 val)
{	
	*(__IO uint16_t *) (Bank1_LCD_R)= index;	
	*(__IO uint16_t *) (Bank1_LCD_D)= val;	
}

/*************************************************
函数名：LCD_RD_Reg
功能：对lcd寄存器，读值
入口参数：寄存器地址
返回值：寄存器值
*************************************************/
u16 LCD_ReadReg(u16 index)
{	
	*(__IO uint16_t *) (Bank1_LCD_R)= index;	
	return (*(__IO uint16_t *) (Bank1_LCD_D));
}

/*************************************************
函数名：LCD_WR_Data
功能：对lcd写数据
入口参数：数据值
返回值：无
*************************************************/
void LCD_WriteData(u16 val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}

/*************************************************
函数名：LCD_RD_Data
功能：读lcd数据
入口参数：无
返回值：数据
*************************************************/
static u16 LCD_ReadData(void)
{
	return(*(__IO uint16_t *) (Bank1_LCD_D));	
}

/*************************************************
函数名：LCD_Power_On
功能：LCD驱动序列
入口参数：无
返回值：无
*************************************************/
static void LCD_PowerOn(void)
{
	LCD_Reset();	 

#if 1
	LCD_DelayMs(50);                     //根据不同晶振速度可以调整延时，保障稳定显示
	LCD_WriteReg(0x00e5, 0x8000);	
	LCD_WriteReg(0x0000, 0x0001);	
	LCD_WriteReg(0x0001, 0x0100);
	LCD_WriteReg(0x0002, 0x0700);
	LCD_WriteReg(0x0003, 0x0030);//使用bgr颜色顺序
	LCD_WriteReg(0x0004, 0x0000);
	LCD_WriteReg(0x0008, 0x0202);	
	LCD_WriteReg(0x0009, 0x0000);	
	LCD_WriteReg(0x000A, 0x0000);
	LCD_WriteReg(0x000C, 0x0000);	
	LCD_WriteReg(0x000D, 0x0000);	
	LCD_WriteReg(0x000F, 0x0000);	
	//-----Power On sequence-----------------------	
	LCD_WriteReg(0x0010, 0x0000);	
	LCD_WriteReg(0x0011, 0x0007);	
	LCD_WriteReg(0x0012, 0x0000);	
	LCD_WriteReg(0x0013, 0x0000);	
	LCD_DelayMs(150);
	LCD_WriteReg(0x0010, 0x17B0);	
	LCD_WriteReg(0x0011, 0x0007);	
	LCD_DelayMs(50);
	LCD_WriteReg(0x0012, 0x013A);	
	LCD_DelayMs(50);
	LCD_WriteReg(0x0013, 0x1A00);	
	LCD_WriteReg(0x0029, 0x000c);		
	LCD_DelayMs(50);
    //-----Gamma control-----------------------	
	LCD_WriteReg(0x0030, 0x0000);	
	LCD_WriteReg(0x0031, 0x0505);	
	LCD_WriteReg(0x0032, 0x0004);	
	LCD_WriteReg(0x0035, 0x0006);	
	LCD_WriteReg(0x0036, 0x0707);	
	LCD_WriteReg(0x0037, 0x0105);	
	LCD_WriteReg(0x0038, 0x0002);	
	LCD_WriteReg(0x0039, 0x0707);	
	LCD_WriteReg(0x003C, 0x0704);	
	LCD_WriteReg(0x003D, 0x0807);	
    //-----Set RAM area-----------------------	
	LCD_WriteReg(0x0050, 0x0000);
	LCD_WriteReg(0x0051, 0x00EF);
	LCD_WriteReg(0x0052, 0x0000);
	LCD_WriteReg(0x0053, 0x013F);
	LCD_WriteReg(0x0060, 0x2700);
	LCD_WriteReg(0x0061, 0x0001);
	LCD_WriteReg(0x006A, 0x0000);
	LCD_WriteReg(0x0021, 0x0000);	
	LCD_WriteReg(0x0020, 0x0000);	
    //-----Partial Display Control------------	
	LCD_WriteReg(0x0080, 0x0000);	
	LCD_WriteReg(0x0081, 0x0000);
	LCD_WriteReg(0x0082, 0x0000);
	LCD_WriteReg(0x0083, 0x0000);
	LCD_WriteReg(0x0084, 0x0000);	
	LCD_WriteReg(0x0085, 0x0000);
    //-----Panel Control----------------------
	LCD_WriteReg(0x0090, 0x0010);	
	LCD_WriteReg(0x0092, 0x0000);
	LCD_WriteReg(0x0093, 0x0003);
	LCD_WriteReg(0x0095, 0x0110);
	LCD_WriteReg(0x0097, 0x0000);	
	LCD_WriteReg(0x0098, 0x0000);
    //-----Display on-----------------------	
	LCD_WriteReg(0x0007, 0x0133);	
	LCD_DelayMs(50);
#else
    /* Start Initial Sequence ------------------------------------------------*/
    LCD_WriteReg(LCD_REG_1, 0x0100);  /* Set SS bit */
    LCD_WriteReg(LCD_REG_2, 0x0700);  /* Set 1 line inversion */
    LCD_WriteReg(LCD_REG_3, 0x1030);  /* Set GRAM write direction and BGR=1. */
    LCD_WriteReg(LCD_REG_4, 0x0000);  /* Resize register */
    LCD_WriteReg(LCD_REG_8, 0x0202);  /* Set the back porch and front porch */
    LCD_WriteReg(LCD_REG_9, 0x0000);  /* Set non-display area refresh cycle ISC[3:0] */
    LCD_WriteReg(LCD_REG_10, 0x0000); /* FMARK function */
    LCD_WriteReg(LCD_REG_12, 0x0000); /* RGB 18-bit System interface setting */
    LCD_WriteReg(LCD_REG_13, 0x0000); /* Frame marker Position */
    LCD_WriteReg(LCD_REG_15, 0x0000); /* RGB interface polarity, no impact */
    /* Power On sequence -----------------------------------------------------*/
    LCD_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    LCD_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
    LCD_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
    LCD_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude */
    LCD_DelayMs(20);                 /* Dis-charge capacitor power voltage (200ms) */
    LCD_WriteReg(LCD_REG_17, 0x0007);  /* DC1[2:0], DC0[2:0], VC[2:0] */
    LCD_DelayMs(5);                   /* Delay 50 ms */
    LCD_WriteReg(LCD_REG_16, 0x12B0);  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    LCD_DelayMs(5);                  /* Delay 50 ms */
    LCD_WriteReg(LCD_REG_18, 0x01BD);  /* External reference voltage= Vci */
    LCD_DelayMs(5); 
    LCD_WriteReg(LCD_REG_19, 0x1400);  /* VDV[4:0] for VCOM amplitude */
    LCD_WriteReg(LCD_REG_41, 0x000E);  /* VCM[4:0] for VCOMH */
    LCD_DelayMs(5);                   /* Delay 50 ms */
    LCD_WriteReg(LCD_REG_32, 0x0000); /* GRAM horizontal Address */
    LCD_WriteReg(LCD_REG_33, 0x013F); /* GRAM Vertical Address */
    /* Adjust the Gamma Curve (SPFD5408B)-------------------------------------*/
    LCD_WriteReg(LCD_REG_48, 0x0b0d);
    LCD_WriteReg(LCD_REG_49, 0x1923);
    LCD_WriteReg(LCD_REG_50, 0x1c26);
    LCD_WriteReg(LCD_REG_51, 0x261c);
    LCD_WriteReg(LCD_REG_52, 0x2419);
    LCD_WriteReg(LCD_REG_53, 0x0d0b);
    LCD_WriteReg(LCD_REG_54, 0x1006);
    LCD_WriteReg(LCD_REG_55, 0x0610);
    LCD_WriteReg(LCD_REG_56, 0x0706);
    LCD_WriteReg(LCD_REG_57, 0x0304);
    LCD_WriteReg(LCD_REG_58, 0x0e05);
    LCD_WriteReg(LCD_REG_59, 0x0e01);
    LCD_WriteReg(LCD_REG_60, 0x010e);
    LCD_WriteReg(LCD_REG_61, 0x050e);
    LCD_WriteReg(LCD_REG_62, 0x0403);
    LCD_WriteReg(LCD_REG_63, 0x0607);
    /* Set GRAM area ---------------------------------------------------------*/
    LCD_WriteReg(LCD_REG_80, 0x0000); /* Horizontal GRAM Start Address */
    LCD_WriteReg(LCD_REG_81, 0x00EF); /* Horizontal GRAM End Address */
    LCD_WriteReg(LCD_REG_82, 0x0000); /* Vertical GRAM Start Address */
    LCD_WriteReg(LCD_REG_83, 0x013F); /* Vertical GRAM End Address */
    LCD_WriteReg(LCD_REG_96,  0xA700); /* Gate Scan Line */
    LCD_WriteReg(LCD_REG_97,  0x0001); /* NDL, VLE, REV */
    LCD_WriteReg(LCD_REG_106, 0x0000); /* set scrolling line */
    /* Partial Display Control -----------------------------------------------*/
    LCD_WriteReg(LCD_REG_128, 0x0000);
    LCD_WriteReg(LCD_REG_129, 0x0000);
    LCD_WriteReg(LCD_REG_130, 0x0000);
    LCD_WriteReg(LCD_REG_131, 0x0000);
    LCD_WriteReg(LCD_REG_132, 0x0000);
    LCD_WriteReg(LCD_REG_133, 0x0000);
    /* Panel Control ---------------------------------------------------------*/
    LCD_WriteReg(LCD_REG_144, 0x0010); 
    LCD_WriteReg(LCD_REG_146, 0x0000);
    LCD_WriteReg(LCD_REG_147, 0x0003);
    LCD_WriteReg(LCD_REG_149, 0x0110);
    LCD_WriteReg(LCD_REG_151, 0x0000);
    LCD_WriteReg(LCD_REG_152, 0x0000);
    /* Set GRAM write direction and BGR=1
       I/D=01 (Horizontal : increment, Vertical : decrement)
       AM=1 (address is updated in vertical writing direction) */
    LCD_WriteReg(LCD_REG_3, 0x1018);
    LCD_WriteReg(LCD_REG_7, 0x0112); /* 262K color and display ON */
//    LCD_SetFont(&LCD_DEFAULT_FONT);
#endif
}

/*************************************************
函数名：LCD_Power_Off
功能：LCD关闭序列
入口参数：无
返回值：无
*************************************************/
static void LCD_PowerOff(void)
{
	return;
}

/*************************************************
函数名：LCD_WR_Data_Start
功能：LCD开始批量传数据前调用
入口参数：无
返回值：无
*************************************************/
void LCD_BlukWriteDataStart(void)
{	
    *(__IO uint16_t *) (Bank1_LCD_R)=GRAMWR;
	//LCD_WriteIndex(GRAMWR);
}

/*************************************************
函数名：LCD_ReadDataStart
功能：LCD开始批量传数据前调用
入口参数：无
返回值：无
*************************************************/
void LCD_BulkReadDataStart(void)
{	
	//LCD_WriteIndex(GRAMWR);
	*(__IO uint16_t *) (Bank1_LCD_R)=GRAMWR;
}

/*************************************************
函数名：LCD_BulkWriteData
功能：对lcd批量写数据
入口参数：数据值
返回值：无
*************************************************/
void LCD_BulkWriteData(u16 val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}

/*************************************************
函数名：LCD_BulkReadData
功能：批量读lcd数据
入口参数：无
返回值：数据
*************************************************/
u16 LCD_BulkReadData(void)
{
  register u16 Data;
  LCD_ReadData();//丢掉无用字节
  Data=LCD_ReadData();
  LCD_WriteData(Data);
  return Data;
}

/*************************************************
函数名：LCD_Set_XY
功能：设置lcd显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void LCD_SetXY(u16 x,u16 y)
{
  LCD_WriteReg(GRAM_XADDR,x);
  LCD_WriteReg(GRAM_YADDR,y);
  LCD_WriteIndex(GRAMWR);
}

/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点,Y_IncMode表示先自增y再自增x
返回值：无
*************************************************/
void LCD_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end,bool xtop)
{		
	*(__IO uint16_t *) (Bank1_LCD_R)=WINDOW_XADDR_START;	
	*(__IO uint16_t *) (Bank1_LCD_D)=x_start;

	*(__IO uint16_t *) (Bank1_LCD_R)=WINDOW_XADDR_END;	
	*(__IO uint16_t *) (Bank1_LCD_D)=x_end;
	

	if(xtop)

		{
			*(__IO uint16_t *) (Bank1_LCD_R)=WINDOW_YADDR_START;	
			*(__IO uint16_t *) (Bank1_LCD_D)=y_start;
			
			*(__IO uint16_t *) (Bank1_LCD_R)=WINDOW_YADDR_END;	
			*(__IO uint16_t *) (Bank1_LCD_D)=y_end;
		
			*(__IO uint16_t *) (Bank1_LCD_R)=0x0003;
			*(__IO uint16_t *) (Bank1_LCD_D)=0x1030; //x自上而下，rgb交换

			*(__IO uint16_t *) (Bank1_LCD_R)=GRAM_XADDR;//设置起始坐标	
			*(__IO uint16_t *) (Bank1_LCD_D)=x_start;
			*(__IO uint16_t *) (Bank1_LCD_R)=GRAM_YADDR;	
			*(__IO uint16_t *) (Bank1_LCD_D)=y_start;
		}
	else

		{
			*(__IO uint16_t *) (Bank1_LCD_R)=WINDOW_YADDR_START;	
			*(__IO uint16_t *) (Bank1_LCD_D)=y_start;
			
			*(__IO uint16_t *) (Bank1_LCD_R)=WINDOW_YADDR_END;	
			*(__IO uint16_t *) (Bank1_LCD_D)=y_end;
		
			*(__IO uint16_t *) (Bank1_LCD_R)=0x0003;
			*(__IO uint16_t *) (Bank1_LCD_D)=0x1010;//x自下而上，rgb交换

			*(__IO uint16_t *) (Bank1_LCD_R)=GRAM_XADDR;	
			*(__IO uint16_t *) (Bank1_LCD_D)=x_start;
			*(__IO uint16_t *) (Bank1_LCD_R)=GRAM_YADDR;	
			*(__IO uint16_t *) (Bank1_LCD_D)=y_end;


		}
	

	*(__IO uint16_t *) (Bank1_LCD_R)=GRAMWR;


	
}

/*************************************************
函数名：LCD_Set_XY_Addr_Direction
功能：设置lcd读或写自增的方向
入口参数：0:由0到高，1:由高到0
返回值：无
*************************************************/
void LCD_SetAddrIncMode(LCD_INC_MODE xyDirection)
{
	register u16 ModeReg=LCD_ReadReg(0x0003);

	ModeReg&=(~0x30);
	ModeReg|=((xyDirection)<<4);
	LCD_WriteReg(0x0003, ModeReg);
}

/*************************************************
函数名：LCD_BGR_Mode
功能：设置lcd RGB顺序
入口参数：0:RGB   1:BGR
返回值：无
*************************************************/
void LCD_BgrMode(bool UseBGR)
{
	register u16 ModeReg=LCD_ReadReg(0x0003);

	if(UseBGR)
		ModeReg&=(~0x1000);
	else
		ModeReg|=(0x1000);
	LCD_WriteReg(0x0003, ModeReg);
	

}

/*************************************************
函数名：LCD_Addr_Inc
功能：地址自增
入口参数：无
返回值：无
*************************************************/
void LCD_AddrInc(void)
{
	register u16 Color16;
	LCD_ReadData();
	Color16=LCD_ReadData();
	LCD_WriteData((((Color16>>11)&0x001f)|(Color16&0x07e0)|((Color16<<11)&0xf800)));//将16位RGB(565)色彩换算成16位BGR(565)色彩
}

/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：无
返回值：无
*************************************************/
void LCD_DrawPoint(u16 x,u16 y,u16 Data)
{
    *(__IO uint16_t *) (Bank1_LCD_R)=GRAM_XADDR;	
	*(__IO uint16_t *) (Bank1_LCD_D)=x;
	*(__IO uint16_t *) (Bank1_LCD_R)=GRAM_YADDR;	
	*(__IO uint16_t *) (Bank1_LCD_D)=y;
	*(__IO uint16_t *) (Bank1_LCD_R)=GRAMWR;
	*(__IO uint16_t *) (Bank1_LCD_D)=Data;
}

/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：无
返回值：无
*************************************************/
u16 LCD_ReadPoint(u16 x,u16 y)
{
  register u16 Data;
    *(__IO uint16_t *) (Bank1_LCD_R)=GRAM_XADDR;	
	*(__IO uint16_t *) (Bank1_LCD_D)=x;
	*(__IO uint16_t *) (Bank1_LCD_R)=GRAM_YADDR;	
	*(__IO uint16_t *) (Bank1_LCD_D)=y;
	*(__IO uint16_t *) (Bank1_LCD_R)=GRAMWR;
  
  Data=(*(__IO uint16_t *) (Bank1_LCD_D)); //丢掉无用字节
  Data=(*(__IO uint16_t *) (Bank1_LCD_D));
  (*(__IO uint16_t *) (Bank1_LCD_D))=Data; //为什么还要把数据写进去？
  return Data;
}
//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
//data :颜色
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 Data)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}   //终点坐标小于起始坐标,反方向,将坐标重新定位为正坐标
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;}   //终点坐标小于起始坐标,反方向,将坐标重新定位为正坐标
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol,Data);//根据坐标画点 
		xerr+=delta_x ;  //X坐标增量
		yerr+=delta_y ;  //Y坐标增量
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
//data：颜色
void Draw_Circle(u8 x0,u16 y0,u8 r,u16 data)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,data);             //3           
		LCD_DrawPoint(x0+b,y0-a,data);             //0           
		LCD_DrawPoint(x0-a,y0+b,data);             //1       
		LCD_DrawPoint(x0-b,y0-a,data);             //7           
		LCD_DrawPoint(x0-a,y0-b,data);             //2             
		LCD_DrawPoint(x0+b,y0+a,data);             //4               
		LCD_DrawPoint(x0+a,y0-b,data);             //5
		LCD_DrawPoint(x0+a,y0+b,data);             //6 
		LCD_DrawPoint(x0-b,y0+a,data);             
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_DrawPoint(x0+a,y0+b,data);
	}
}
/**********************************************
函数名：FSMC_LCD_Init
功能：用于FSMC配置
入口参数：无
返回值：无
***********************************************/
static void LCD_FSMC_Init(void)
{
 
	RCC->AHBENR|=0x00000100; 
	//寄存器清零
	//bank1有NE1~4,每一个有一个BCR+TCR，所以总共八个寄存器。
	//这里我们使用NE1 ，也就对应BTCR[0],[1]。				    
//	FSMC_Bank1->BTCR[0]=0X00000000;
//	FSMC_Bank1->BTCR[1]=0X00000000;
//	FSMC_Bank1E->BWTR[0]=0X00000000;
	//操作BCR寄存器	使用异步模式
 
 	FSMC_Bank1->BTCR[0]=0x00|(0x10<<2)|(0x01<<4)|(1<<6)|(1<<12); 
	FSMC_Bank1->BTCR[1]=0x02|(0x00<<4)|(0x05<<8)|(0x00<<16)|(0x00<<24)|(0x01<<28); 	 
	//闪存写时序寄存器  
	FSMC_Bank1E->BWTR[0]=0x0FFFFFFF;//默认值
	//使能BANK1
	FSMC_Bank1->BTCR[0]|=1<<0;
  
}

/**********************************************
函数名：LCD_Configuration
功能：用于LCD的IO配置
入口参数：延时数
返回值：无
***********************************************/
static void LCD_Configuration(void)
{



  RCC->APB2ENR|=0X71;	  //AFIO PC PDP PE
  //LCD 背光控制,	  驱动ic背光控制
  GPIOC->CRL&=0X00FFFFFF;
  GPIOC->CRL|=0X33000000;
  GPIOD->CRH&=0XFF0FFFFF;
  GPIOD->CRH|=0X00300000;
  //FSMC的GPIOD管脚
  GPIOD->CRL&=0X0F00FF00;
  GPIOD->CRL|=0XB0BB00BB;
  GPIOD->CRH&=0X00FF0000;
  GPIOD->CRH|=0XBB00BBBB;

  GPIOE->CRL&=0X0FFFFFFF;
  GPIOE->CRL|=0XB0000000;
  GPIOE->CRH&=0X00000000;
  GPIOE->CRH|=0XBBBBBBBB;
}

/*************************************************
函数名：LCD_Init
功能：初始化启动lcd
入口参数：无
返回值：无
*************************************************/
void LCD_Init(void)
{	
	LCD_FSMC_Init();
	LCD_DelayMs(100);	 
	LCD_Configuration();
	LCD_ILI9320_On();
	LCD_DelayMs(100);
	LCD_Light_On();
	LCD_PowerOn();
	//LCD_BgrMode(TRUE);
}

void LCD_DeInit(void)
{
	LCD_PowerOff();
}

/**********************************************
函数名：LCD_Reset
功能：LCD复位
入口参数：延时数
返回值：无
***********************************************/ 
void LCD_Reset(void)
{
	GPIOD->BRR=0X2000;
	//GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    LCD_DelayMs(50);
	GPIOD->BSRR=0X2000;					   
    //GPIO_SetBits(GPIOD, GPIO_Pin_13);		 	 
	LCD_DelayMs(50);	
}


//从ILI93xx读出的数据为GBR格式，而我们写入的时候为RGB格式。
//通过该函数转换
//c:GBR格式的颜色值
//返回值：RGB格式的颜色值
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
}

/****************************************************************************
* 名    称：Fill
* 功    能：填充一块颜色
* 入口参数：填充起始点，填充的长宽，填充颜色
* 出口参数：无
****************************************************************************/
void LCD_Fill(u16 x,u16 y,u16 b,u16 h,u16 Color)
{
	u32 temp;  
	
	LCD_SetRegion(x,y,x+b-1,y+h-1,1);
 
	for (temp = 0; temp < b*h; temp++)
	{
		*(__IO uint16_t *) (Bank1_LCD_D)= Color;
	} 
}
/****************************************************************************
* 名    称：Clear
* 功    能：填充一块颜色
* 入口参数：填充颜色
* 出口参数：无
****************************************************************************/
void LCD_Clear(u16 Color)
{
	u32 temp;  
	
	LCD_SetRegion(0,0,239,319,FALSE);
 
	for (temp = 0; temp < 240*320; temp++)
	{
		*(__IO uint16_t *) (Bank1_LCD_D)= Color;
	} 
}
/************************************************
函数名：PutChar
功能：在某个坐标上写一个ASCII表内的字符
入口参数：xy坐标，字和颜色
返回值：无
************************************************/
void PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;  
  u8 temp=0;

  LCD_SetRegion(0,0,239,319,FALSE);
  
  for (i=0;i<16;i++)
  {
    temp=ascii_8x16[((c-0x20)*16)+i];
    for (j=0;j<8;j++)
    {
      if ( (temp >> 7-j) & 0x01 == 0x01)
        {
          LCD_DrawPoint(x+j,y+i,charColor); // 字符颜色
        }
        else
        {
          LCD_DrawPoint(x+j,y+i,bkColor); // 背景颜色
        }
    }
  }
}
//显示字符串
//x,y:起点坐标  
//*p:字符串起始地址
//用16字体


/****************************************************************************
* 名    称：DisplayString
* 功    能：显示字符，包括中文英文，自动换行显示
* 入口参数：x，y坐标 *是str指向字符串的指针 charColor字符颜色 bkColor背景颜色 
			若bkColor=1，则为透明背景
* 出口参数：无
* 注意    ：暂时未加入中文标点，标点请用英文标点
****************************************************************************/
void DisplayString(u16 x,u16 y, u8 *str, u16 charColor, u16 bkColor)
{
  u16 i,j;
  u8 tmp=0;
  u16 tmp16=0;
  u8 buf[32];
  u32 pos;

  LCD_SetRegion(0,0,239,319,FALSE);
  while (*str != 0)
  {
  	if(*str <127)
	{
		for (i=0;i<16;i++)
		{
		    tmp=ascii_8x16[((*str-0x20)*16)+i];
		    for (j=0;j<8;j++)
		    {
		      if ( (tmp >> 7-j) & 0x01 == 0x01)
		        {
		          LCD_DrawPoint(x+j,y+i,charColor); // 字符颜色
		        }
		       else
		        {
		          if(bkColor != 1) 
				  	LCD_DrawPoint(x+j,y+i,bkColor); // 背景颜色 ,把白色设为透明背景
		        }
		    }
		 }
		 str++;
		 x+=8;
		 if(x>224)
		 {
		 	x=0;
			y+=16;
		 }	
	}
#if 0
	else
	{
		 	pos =( ( ( (*(str++)-0xb0 )*94 + *(str)-0xa1) )<<5);
			GPIOB->CRL&=0XFF000FFF;
			GPIOB->CRL|=0X00B8B000; 
			M25P16_Fast_Read_Data((GB2312_TABLE_BASE<<8)+pos,32,buf);
			for (i=0;i<16;i++)
	        {
	            tmp16=(buf[i*2]<<8)+buf[2*i+1];
	            //tmp16=(tmp16<<8);
	            //tmp16 |=buf[2*i+1];
				//printf("%x  \n",tmp16);
	            for (j=0;j<16;j++)
	            {
	                
	                if ( (tmp16 >> 15-j) & 0x01 == 0x01)
	                {
	                    LCD_DrawPoint(x+j,y+i,charColor); // 字符颜色
	                }
	                else
	                {
	                    if(bkColor != 1) 
				  		LCD_DrawPoint(x+j,y+i,bkColor); // 背景颜色 ,把白色设为透明背景
	                }
	            }
	        }
			str++;
			x+=16;
			if(x>224)
			 {
			 	x=0;
				y+=16;
			 }

		}
#endif
 
  }
}
/****************************************************************************
* 名    称：void Show_Bmp16bit(u16 x,u16 y,u16 b,u16 h,bu16 *addr)
* 功    能：显示16位数据的bmp图片
* 入口参数：显示的起始xy坐标，图片长宽，数据地址
* 出口参数：无  
****************************************************************************/
void Show_Bmp16bit(u16 x,u16 y,u16 b,u16 h,u8 *addr)
{
	u16 low,hig;
	u16 a,c;

	LCD_SetRegion(0,0,239,319,FALSE);
	LCD_SetXY(x,y);

	for(c=y;c<y+h;c++)
	{
		for(a=x;a<x+b;a++)
		{
			low=*addr++;
			hig=*addr++;
			hig=hig<<8;
			low=low+hig;		
//			LCD_DrawPoint(a,c,low);
			LCD_WriteData(low);
		}	
	}
}
