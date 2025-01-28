#include <LiquidCrystal.h>  

#define SW3_3 9

LiquidCrystal lcd( 2, 15, 17, 16, 4, 0);                       // RS, E, D4, D5, D6, D7  

byte customChar0[8] = {B00000, B00000, B00000, B00010, B00010, B00010, B00010, B00011};
byte customChar1[8] = {B00001, B01111, B00000, B01110, B10001, B01001, B10001, B10001};
byte customChar2[8] = {B00000, B00000, B00000, B11001, B10001, B01001, B10001, B11111};
byte customChar3[8] = {B00000, B00000, B00000, B01110, B10001, B01100, B00010, B01100};
byte customChar4[8] = {B00000, B11111, B00000, B01010, B10101, B10001, B10101, B11001};
byte customChar5[8] = {B11010, B01101, B00010, B11111, B10001, B10101, B11001, B10001};
byte customChar6[8] = {B00000, B00000, B00000, B01110, B10001, B01001, B10001, B10001};
byte customChar7[8] = {B00001, B00011, B11100, B00000, B01110, B10001, B10101, B11001};

char text[] = {0, 1, 2, 3, 4, 5, 6, 7, ' ', 'K', 'i', 'e', 't', 't', 'i', 's', 'a', 'k', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' '};
int length = sizeof(text);
int screenWidth = 16;

int pos = 0;
int count = 0;
int i = 0;

void setup() { 
  lcd.begin(16, 2); 
  pinMode(12,INPUT);  
  pinMode(13,OUTPUT);
  pinMode(SW3_3, INPUT);

  lcd.createChar(0, customChar0);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);
  lcd.createChar(6, customChar6);
  lcd.createChar(7, customChar7);
 
  lcd.setCursor(1,0); 
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)1);
  lcd.write((uint8_t)2);
  lcd.write((uint8_t)3); 
  lcd.write((uint8_t)4);
  lcd.write((uint8_t)5);
  lcd.write((uint8_t)6);
  lcd.write((uint8_t)7);
 
  lcd.print(" Kiettisak");
  lcd.setCursor(2,1); 
  lcd.print("AI engineer"); 
} 

void loop() {
	int st = digitalRead(SW3_3);

  lcd.setCursor(0, 0);

  int j = (pos + i) % length;

  if (text[j] >= 0 && text[j] <= 7)
  {
      lcd.write(byte(text[j]));
  }
  else
  {
      lcd.print(text[j]);
  }

  if(st)
	  i++;
  else
	  i--;


  i = (i + screenWidth) % screenWidth;

  pos = (pos + 1) % length;

  delay(100);
} 
