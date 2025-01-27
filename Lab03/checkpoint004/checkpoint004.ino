#include <LiquidCrystal.h>  

LiquidCrystal lcd( 2, 15, 17, 16, 4, 0);    // RS, E, D4, D5, D6, D7 

char myString[64];  
byte customChar0[] = {B00011, B11011, B11111, B00001, B01101, B00101, B00101, B00111};//ป  
byte customChar1[] = {B00000, B00000, B00000, B11101, B10101, B10101, B10111, B00010};//ญ 
byte customChar2[8] = {B00000, B00000, B00000, B01101, B01001, B00101, B01001, B01111};//ย 
byte customChar3[] = {B00000, B00001, B00001, B01111, B01001, B01101, B01001, B01001};//ศ 

void setup() { 
  lcd.begin(16, 2); 
  pinMode(12,INPUT);  pinMode(13,OUTPUT); 
 
  lcd.createChar(0, customChar0); //ป 
  lcd.createChar(1, customChar1); //ญ 
  lcd.createChar(2, customChar2); //ย 
  lcd.createChar(3, customChar3); //ศ 
   
  lcd.setCursor(1,0); 
  lcd.write((uint8_t)0);//ป 
  lcd.write((uint8_t)1);//ญ 
  lcd.write((uint8_t)1);//ญ 
  lcd.write((uint8_t)2);//ย 
  lcd.write((uint8_t)3);//ศ  
  lcd.print(" Panyayot"); 
  lcd.setCursor(2,1); 
  lcd.print("Computer Eng"); 
} 
 
void loop() {  } 
