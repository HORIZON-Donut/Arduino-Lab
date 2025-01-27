#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd1(2, 15, 17, 16, 4, 0);
void setup() {
  lcd1.begin(16, 2);
  lcd1.clear();
}

void loop() {

  lcd1.clear();
  
  String name = "Kiettisak";
  String surname = "Sea-iw    ";

  int name_length = name.length();
  int surname_length = surname.length();
  
  for(int i = 0; i <= name_length; i++)
  {
    lcd1.setCursor(16 - i, 0);
    lcd1.print(name[name_length - i]);

    lcd1.setCursor(i, 1);
    lcd1.print(surname[i]);
    delay(500);
  }

  delay(3000);
}
