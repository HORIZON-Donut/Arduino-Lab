#include "wiring_shift_mod.h"

#define CLOCK_TYPE CLOCK_INVERT
#define CLOCK_DELAY_US 1

const int strobe = 17;
const int s_clk = 16;
const int data1 = 4;

char BCD_TO_7SEGMENT (uint8_t A)
 {
   static char LOOKUPTB[ ] =
   {  
    0x3F, 
    0x06,
    0x5B, 
    0x4F,
    0x66, 
    0x6D,
    0x7D, 
    0x07,
    0x7F, 
    0x6F,
    0x77, 
    0x7C,
    0x39, 
    0x5E,
    0x79, 
    0x71
  };
   return LOOKUPTB[A];
}

/*-------------------------------------------------
---- แอลอีดี 7 เซกเมนต์มี 8 หลัก 
---- หลักซ้ายสุด คือ หลัก 0
---- หลักขวาสุด คือ หลัก 7
---------------------------------------------------
---- digit คือ หมายเลขหลักที่จะแสดงผลบนแอลอีดี 7 เซกเมนต์
---- num คือ ตัวเลขที่จะแสดงผลบน 7 เซกเมนต์
---------------------------------------------------
*/
void DISP_NUM_to_7SEG(char digit, uint8_t num)
{  
  char data;  
  char address = 0xc0;
  digit = digit << 1;
  address |= digit;
  data = BCD_TO_7SEGMENT(num);
  digitalWrite(strobe, LOW);
  shiftOutMod(data1, s_clk, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, address);  //1st digit
  shiftOutMod(data1, s_clk, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, data);
  digitalWrite(strobe, HIGH); 
}



void sendCommand(uint8_t value)
{
  digitalWrite(strobe, LOW);
  shiftOutMod(data1, s_clk, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, value);
  digitalWrite(strobe, HIGH);
}

void reset()
{
  sendCommand(0x40); // set auto increment mode
  digitalWrite(strobe, LOW);
  shiftOutMod(data1, s_clk, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, 0xc0);   // set starting address to 0
  for(uint8_t i = 0; i < 16; i++)
  {
    shiftOutMod(data1, s_clk, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, 0x00);
  }
  digitalWrite(strobe, HIGH);
}

//--------------------------------------------------------------------------
//------------------------------------SETUP---------------------------------
//--------------------------------------------------------------------------
void setup()
{
  char i;
  pinMode(strobe, OUTPUT);
  pinMode(s_clk, OUTPUT);
  pinMode(data1, OUTPUT);

  sendCommand(0x8f);  // activate
  reset();

  //----สั่งให้ 7 เซกเมนต์แสดงค่า 12345678
  sendCommand(0x44);  // set single address
  for (i=0;i <8;i++)
  {
    DISP_NUM_to_7SEG(i,i+1);
  }
}

unsigned long number = 99995000;

//--------------------------------------------------------------------------
//------------------------------------LOOP----------------------------------
//--------------------------------------------------------------------------
void loop()
{
  unsigned long tmp = number;
  for(int i = 0; i < 8; i++)
  {
    int digit = tmp % 10;
    DISP_NUM_to_7SEG(7 - i, digit);
    tmp /= 10;
  }

  number += 1;

  if(number > 99999999)
  number = 0;
}  
