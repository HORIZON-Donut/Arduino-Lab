#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 15, 17, 16, 4, 0);
void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursir(2, 0);
  lcd.print("Start up");
  delay(3000);
}

void loop() {
}
