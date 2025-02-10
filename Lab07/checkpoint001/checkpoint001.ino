#include <Arduino.h> 

#define SegA 4
#define SegB 0
#define SegC 17
#define SegD 16
#define SegE 23
#define SegF 19
#define SegG 18
#define DP 5
#define digit10 14
#define digit01 27

const int ITR_1 = 21;
const int ITR_2 = 22; 
const unsigned long debounceDelay = 200; // 200 ms 

int num_int=0;
int Digit01 = 0;
int Digit10 = 0;

volatile unsigned long lastInterruptTime = 0; 

char BIN_TO_7SEGMENT2(char A)
{
	static char LOOKUPTB[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

	return LOOKUPTB[A];
}

void display7segment(char data)
{
	(data & 0x01)? digitalWrite(SegA, HIGH):digitalWrite(SegA, LOW);
	(data & 0x02)? digitalWrite(SegB, HIGH):digitalWrite(SegB, LOW);
	(data & 0x04)? digitalWrite(SegC, HIGH):digitalWrite(SegC, LOW);
	(data & 0x08)? digitalWrite(SegD, HIGH):digitalWrite(SegD, LOW);
	(data & 0x10)? digitalWrite(SegE, HIGH):digitalWrite(SegE, LOW);
	(data & 0x20)? digitalWrite(SegF, HIGH):digitalWrite(SegF, LOW);
	(data & 0x40)? digitalWrite(SegG, HIGH):digitalWrite(SegG, LOW);

}

void Display()
{
	char disp_v = 0;

	char tmp01 = BIN_TO_7SEGMENT2(Digit01);
	char tmp10 = BIN_TO_7SEGMENT2(Digit10);

	for(char i = 0; i < 100; i++)
	{
		display7segment(tmp01);
		digitalWrite(digit01, HIGH);
		digitalWrite(digit10, LOW);
		delay(2);

		display7segment(tmp10);
		digitalWrite(digit01, LOW);
		digitalWrite(digit10, HIGH);
		delay(2);
	}
}

void IRAM_ATTR ISR_1() 
{ 
 unsigned long interruptTime = millis(); 
 if (interruptTime - lastInterruptTime > debounceDelay) 
 { 
 num_int++; 
 Serial.print("Interrupt from ITR_1 is detected!-->"); 
 Serial.println(num_int); 
 lastInterruptTime = interruptTime; 
 } 
} 

void IRAM_ATTR ISR_2() 
{ 
 unsigned long interruptTime = millis(); 
 if (interruptTime - lastInterruptTime > debounceDelay) 
 { 
 num_int--; 
 Serial.print("Interrupt from ITR_2 is detected!-->"); 
 Serial.println(num_int); 
 lastInterruptTime = interruptTime; 
 } 
} 

void setup() 
{ 
 pinMode(ITR_1, INPUT_PULLUP); // Set SW31 as input with internal pull-up 
 pinMode(ITR_2, INPUT_PULLUP);
 pinMode(SegA, OUTPUT);
	pinMode(SegB, OUTPUT);
	pinMode(SegC, OUTPUT);
	pinMode(SegD, OUTPUT);	
	pinMode(SegE, OUTPUT);
	pinMode(SegF, OUTPUT);
	pinMode(SegG, OUTPUT);
	pinMode(DP, OUTPUT);
	pinMode(digit10, OUTPUT);
	pinMode(digit01, OUTPUT);

 attachInterrupt(digitalPinToInterrupt(ITR_1), ISR_1, FALLING); 
 attachInterrupt(digitalPinToInterrupt(ITR_2), ISR_2, FALLING);
 Serial.begin(9600); 
} 
void loop() 
{
  if(num_int > 9)
  {
    Digit10++;
    num_int = 0;
  }
  else if(num_int < 0)
  {
    Digit10--;
    num_int = 9;
  }

  if(Digit10 > 9)
  {
    Digit10 = 0;
  }
  else if(Digit10 < 0)
  {
    Digit10 = 9;
  }

  Digit01 = num_int;

  Display();
} 
