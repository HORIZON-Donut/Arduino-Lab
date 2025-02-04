#include <Wire.h> 
#include <LiquidCrystal.h>

#include "RTClib.h" 

#define I2CADDR 0x20  

LiquidCrystal lcd(2, 15, 17, 16, 4, 0); 
RTC_DS1307 rtc; 
DateTime now; 
Keypad_I2C keypad(I2CADDR, 2); 

int hour;
int minute;
int isSet;

void display_date_LCD(void)
{
  now = rtc.now();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  lcd.setCursor(1, 1);
  lcd.print(hour);
  lcd.print(':');
  lcd.print(minute);

  lcd.setCursor(9, 1);
  switch(isSet)
  {
    case 0:
      lcd.print("Off");
      break;

    case 1:
      lcd.print("On");
      break;

    default:
      lcd.print("Off");
      break;
  }
}

void display_date_serial_monitor(void) 
{ 
    now = rtc.now(); 
    Serial.print(now.hour(), DEC); 
    Serial.print(':'); 
    Serial.print(now.minute(), DEC); 
    Serial.print(':'); 
    Serial.print(now.second(), DEC); 
    Serial.println(); 
    Serial.println(); 
}

void setTime()
{
  int digit01 = 0;
  int digit10 = 0;
  int nextDigit = 0;
  
  while(1)
  {
    char key = keypad.getKey();
    if(key == 'A')
    {
      break;
    }
    else
    {
      if(nextDigit == 0)
      {
        digit01 = (int)keypad.getKeyNum();
        nextDigit+= 1;
      }
      else
      {
        digit10 = (int)keypad.getKeyNum();
        nextDigit = 0;
      }
    }

    hour = digit01 * 10 + digit10;
    display_date_LCD();
    delay(100);
  }

    while(1)
  {
    char key = keypad.getKey();
    if(key == 'A')
    {
      break;
    }
    else
    {
      if(nextDigit == 0)
      {
        digit01 = (int)keypad.getKeyNum();
        nextDigit+= 1;
      }
      else
      {
        digit10 = (int)keypad.getKeyNum();
        nextDigit = 0;
      }
    }

    minute = digit01 * 10 + digit10;
    display_date_LCD();
    delay(100);
  }
}

void setup ()  
{
  hour = 0;
  minute = 0;
  isSet = 0;
  
  lcd.begin(16, 2);
  lcd.clear();

  Wire.begin( ); 
  keypad.begin( );
  
  Serial.begin(9600); 
  delay(3000); // wait for console opening 
 
  if (! rtc.begin()) { 
    Serial.println("Couldn't find RTC"); 
    while (1); 
  } 
 
  if (!rtc.isrunning()) { 
    Serial.println("RTC lost power, lets set the time!"); 
    rtc.adjust(DateTime(2025, 2, 4, 13, 56, 0)); 
  } 
}
 
void loop ()  
{ 
  char key = keypad.getKey(); 
  
  display_date_serial_monitor();
  display_date_LCD();

  switch(key)
  {
    case 'A':
      //
      break;
    case 'C':
      //
      break;
    default:
      //
      break;
  }
  delay(5000);
}
