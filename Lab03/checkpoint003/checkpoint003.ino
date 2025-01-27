#include <Wire.h>
#include <LiquidCrystal.h>

String name;
String surname;

int length;

LiquidCrystal lcd1(2, 15, 17, 16, 4, 0);
void setup() {
  lcd1.begin(16, 2);
  lcd1.clear();

  name = "Kiettisak";
  surname = "Sea-iw   ";
  length = (name.length() >= surname.length()) ? name.length() : surname.length();
}

void loop() {
  
  for(int i = 0; i <= name_length; i++)
  {
    lcd1.setCursor(16 - i, 0);
    lcd1.print(name[name_length - i]);

    lcd1.setCursor(i, 1);
    lcd1.print(surname[i]);
    delay(500);
  }

}
