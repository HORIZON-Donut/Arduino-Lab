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
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < 16 - i; j ++)
    {
      lcd1.setCursor(j, 0);
      lcd1.print(name[length - i]);

      if (j !=0 )
      {
        lcd1.setCursor(j - 1, 0);
        lcd1.print(" ");
      }

      lcd1.setCursor(15 - j, 1);
      lcd1.print(surname[i]);

      lcd1.setCursor(15 - j + 1, 1);
      lcd1.print(" ");

      delay(100);
    }
  }
}