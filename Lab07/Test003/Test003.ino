#include <Arduino.h> 
const int SW3_1 = 34; 
const unsigned long debounceDelay = 200; // 200 ms 
int num_int=0; 
volatile unsigned long lastInterruptTime = 0; 
void IRAM_ATTR ISR_SW31() 
{ 
 unsigned long interruptTime = millis(); 
 if (interruptTime - lastInterruptTime > debounceDelay) 
 { 
 num_int++; 
 Serial.print("Interrupt from SW3_1 is detected!-->"); 
 Serial.println(num_int); 
 lastInterruptTime = interruptTime; 
 } 
} 
void setup() 
{ 
 pinMode(SW3_1, INPUT_PULLUP); // Set SW31 as input with internal pull-up 
 attachInterrupt(digitalPinToInterrupt(SW3_1), ISR_SW31, FALLING); 
 Serial.begin(115200); 
} 
void loop() 
{ 
 // Main loop can continue to run other tasks while waiting for interrupt 
} 