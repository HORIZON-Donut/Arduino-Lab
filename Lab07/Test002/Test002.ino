#include <Arduino.h> 
const int SW3_1 = 34; 
int num_int=0; 
void IRAM_ATTR ISR_SW31() 
{ 
 num_int++; 
 Serial.print("Interrupt from SW3_1 is detected!-->"); 
 Serial.println(num_int); 
} 
void setup() 
{ 
 pinMode(SW3_1, INPUT_PULLUP); // Set SW3_1 as input with internal 
 // pull-up resistor 
 attachInterrupt(digitalPinToInterrupt(SW3_1), ISR_SW31, FALLING); 
 Serial.begin(115200); 
} 
void loop() 
{ 
 
}