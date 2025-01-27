#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd1(2, 15, 17, 16, 4, 0);
void setup() {
  lcd1.begin(16, 2);
  lcd1.clear();
}

void loop() {
  lcd1.setCursor(0, 0); 
  lcd1.print(" Hello TEST!!!!"); 
  lcd1.setCursor(0, 1); 
  lcd1.print("Department of Computer Engineering"); 
  delay(2000); 
  for (int i=0;i<18;i++) { 
    lcd1.scrollDisplayLeft(); 
    delay(200); 
  } 
  delay(2000); 
  for (int i=0;i<18;i++) { 
    lcd1.scrollDisplayRight(); 
    delay(200); 
  } 
  delay(2000); 
  for (int i=0;i<3;i++) { 
    lcd1.noDisplay(); 
    delay(500); 
    lcd1.display(); 
    delay(500); 
  } 
  delay(3000); // หน่วงเวลา 3 วินาที
  lcd1.clear();
}
