#include "Init_SYS.h"

void delay_us(u32 Nus)
{ 
 SysTick->LOAD=9*Nus;       //ʱ�����      
 SysTick->CTRL|=0x01;            //��ʼ����    
 while(!(SysTick->CTRL&(1<<16)));//�ȴ�ʱ�䵽�� 
 SysTick->CTRL=0X00000000;       //�رռ�����
 SysTick->VAL=0X00000000;        //��ռ�����     
}
void delay_ms(u32 Nus)
{ 
 SysTick->LOAD=9000*Nus;       //ʱ�����      
 SysTick->CTRL|=0x01;            //��ʼ����    
 while(!(SysTick->CTRL&(1<<16)));//�ȴ�ʱ�䵽�� 
 SysTick->CTRL=0X00000000;       //�رռ�����
 SysTick->VAL=0X00000000;        //��ռ�����     
}
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)	 
{ 
  	//�������Ϸ���
	assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
	assert_param(IS_NVIC_OFFSET(Offset));  	 
	SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);//����NVIC��������ƫ�ƼĴ���
	//���ڱ�ʶ����������CODE��������RAM��
}
//����NVIC����
//NVIC_Group:NVIC���� 0~4 �ܹ�5�� 
//CHECK OK
//091209/
void MyRCC_DeInit(void)
{										  					   
	RCC->APB1RSTR = 0x00000000;//��λ����			 
	RCC->APB2RSTR = 0x00000000; 
	  
  	RCC->AHBENR = 0x00000014;  //˯��ģʽ�����SRAMʱ��ʹ��.�����ر�.	  
  	RCC->APB2ENR = 0x00000000; //����ʱ�ӹر�.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //ʹ���ڲ�����ʱ��HSION	 															 
	RCC->CFGR &= 0xF8FF0000;   //��λSW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //��λHSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //��λHSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //��λPLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //�ر������ж�
	//����������				  
#ifdef  VECT_TAB_RAM
	MY_NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else   
	MY_NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
}


void RCC_Configuration()
{
	unsigned char temp=0;
	uint8_t PLL=9;//9��Ƶ���   
	MyRCC_DeInit();		  //��λ������������
	RCC->CR|=0x00010000;  //�ⲿ����ʱ��ʹ��HSEON
	while(!(RCC->CR>>17));//�ȴ��ⲿʱ�Ӿ���
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;//����2����λ
	RCC->CFGR|=PLL<<18;   //����PLLֵ 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	FLASH->ACR|=0x32;	  //FLASH 2����ʱ����

	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//�ȴ�PLL����
	RCC->CFGR|=0x00000002;//PLL��Ϊϵͳʱ��	 
	while(temp!=0x02)     //�ȴ�PLL��Ϊϵͳʱ�����óɹ�
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}    
}

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);


#ifdef USART1_IRQ
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);
#endif
}

#ifdef USART1_IRQ   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[64];     //���ջ���,���64���ֽ�.
//����״̬
//bit7��������ɱ�־
//bit6�����յ�0x0d
//bit5~0�����յ�����Ч�ֽ���Ŀ
u8 USART_RX_STA=0;       //����״̬���	  
  
void USART1_IRQHandler(void)
{
	u8 res;

		    
		if(USART1->SR&(1<<5))//���յ�����
		{	 
			res=USART1->DR; 
		
			if(res==0x0d)	 //0X0D���ڴ��ڵ��������������Զ���Ӹ���λΪ0x0d
			{
				USART_RX_STA|=0x80;
				
			}
			else
			{
				USART_RX_BUF[USART_RX_STA&0X7F]=res;
				USART_RX_STA++;
				if((USART_RX_STA&0X7F)>63)USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
			}		 
		}
		  		 									     
	  											 
} 
#endif
void GPIO_Configuration(void)
{  
  /* Enable GPIO_LED clock */
	RCC->APB2ENR|=1<<4;//ʹ��GPIOCʱ��
	//LED_init-------------------------------------------------------
	////���ùܽ�
	GPIOC->CRL&=0XFFFFF000;
	GPIOC->CRL|=0x00000333; 
  
}

void UART_Init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F; 
	GPIOA->CRH|=0X000008B0;//IO״̬����
		  
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
#ifdef USART1_IRQ		  //���ʹ���˽���
	//ʹ�ܽ����ж�
	USART1->CR1|=1<<8;    //PE�ж�ʹ��
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	
#endif

}


/*----------------------------------------------------------------------------
  �Ӵ��ڷ���һ���ֽ�����
  Write character to Serial Port.
 *----------------------------------------------------------------------------*/
int SendChar (int ch)  {

  //�ȴ����ͽ���
  while (!(USART1->SR & 0X80));
  //�����ݷ��뷢�ͼĴ���
  USART1->DR = (ch & 0x1FF);

  return (ch);
}

/*----------------------------------------------------------------------------
  �Ӵ��ڶ�ȡһ���ֽ����ݣ�ֱ���������ݲŷ���
  Read character to Serial Port.
 *----------------------------------------------------------------------------*/
int GetKey (void)  {

  //�ȴ����ս���
  while (!(USART1->SR & 0X40));
  //�ӽ��ܼĴ�����ȡ���ݲ�����
  return ((int)(USART1->DR & 0x1FF));
}
