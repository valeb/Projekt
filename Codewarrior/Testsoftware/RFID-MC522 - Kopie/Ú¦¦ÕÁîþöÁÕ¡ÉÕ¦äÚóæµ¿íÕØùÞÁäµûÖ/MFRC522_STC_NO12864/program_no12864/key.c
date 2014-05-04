#include "include.h"

sbit  line1=P3^7;
sbit  line2=P2^3;
sbit  row1=P3^6;
sbit  row2=P2^4;

#define  SET_LINE1  line1=1
#define  CLR_LINE1  line1=0
#define  SET_LINE2  line2=1
#define  CLR_LINE2  line2=0

#define  STU_ROW1  row1
#define  STU_ROW2  row2

extern uchar data KeyTime;

uchar GetKey(void)
{
  //uchar tmp=0;
  SET_LINE1;
  SET_LINE2;
  CLR_LINE1;
  
  nop();
  if((STU_ROW1==0)&&(!KeyTime))
  {
    return N_1;
  }
  else if((STU_ROW2==0)&&(!KeyTime))
  {
    return N_3;
  }
  
  SET_LINE1;
  SET_LINE2;
  CLR_LINE2;
  nop();
  if((STU_ROW1==0)&&(!KeyTime))
  {
    return N_2;
  }
  else if((STU_ROW2==0)&&(!KeyTime))
  {
    return N_4;
  }  
  
  return N_NOP; 
}