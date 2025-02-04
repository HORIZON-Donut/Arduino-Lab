#include "wiring_shift_mod.h"

#define CLOCK_TYPE CLOCK_INVERT
#define CLOCK_DELAY_US 1

const int strobe = 17;
const int s_clk = 16;
const int data1 = 4;

void setLed(uint8_t position, uint8_t value)
{
  pinMode(data1, OUTPUT);

  sendCommand(0x44);
  digitalWrite(strobe, LOW);
  shiftOutMod(data1, s_clk, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, 0xC1 + (position << 1));
  shiftOutMod(data1, s_clk, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, value);
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

  //----สั่งให้แอลอีดีดับทุกดวง
  sendCommand(0x44);  // set single address
  for (i=0;i <8;i++)
  {
    setLed(i,0);
  }
}



//--------------------------------------------------------------------------
//------------------------------------LOOP----------------------------------
//--------------------------------------------------------------------------
void loop()
{
  char i;
  for (i=0;i <8;i++)
    setLed(i,0);
  delay(1000);
  for (i=0;i <8;i++)
    setLed(i,1);
  delay(1000);
}  
