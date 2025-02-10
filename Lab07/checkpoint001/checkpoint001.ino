#include <Arduino.h> 
const int ITR_1 = 34;
const int ITR_2 = 35; 
const unsigned long debounceDelay = 200; // 200 ms 

int num_int=0; 
volatile unsigned long lastInterruptTime = 0; 

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
 attachInterrupt(digitalPinToInterrupt(ITR_1), ISR_1, FALLING); 
 attachInterrupt(digitalPinToInterrupt(ITR_2), ISR_2, FALLING);
 Serial.begin(9600); 
} 
void loop() 
{ 
 // Main loop can continue to run other tasks while waiting for interrupt 
} 
