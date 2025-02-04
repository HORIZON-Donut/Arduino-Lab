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
int isSetting;

void display_date_LCD(int n, value)
{
  now = rtc.now();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);

  if(n == 0)
  {
    
  }
  else if(n == 1)
  {
    lcd.setCursor(1, 1);
    lcd.print(value);
  
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

int GetNumber()
{
  int digit01 = 0;
  int digit10 = 0;
  int nextDigit = 0;
  
  while(isSetting)
  {
    char key = keypad.getKey();
    if(key == '#')
    {
      isSet = 1;
      isSetting = 0;
      break;
    }
    if(key == 'A')
    {
      break;
    }
    if(key <= '9' && key <= '0')
    {
      if(nextDigit == 0)
      {
        digit01 = (int)key();
        nextDigit+= 1;
      }
      else
      {
        digit10 = (int)key();
        nextDigit = 0;
      }
    }
    lcd.print(digit01);
    lcd.print(digit10);
    display_date_LCD(1, digit01 * 10 + digit10);
    delay(200);
  }

  return digit01 * 10 + digit10;
}

void setTime()
{
  hour = GetNumber();
  hour = (hour > 23) ? 23:hour;

  minute = GetNumber();
  minute = (minute > 59) ? 59:minute;

  isSetting = 1;
}

void setup ()  
{
  hour = 0;
  minute = 0;
  isSet = 0;
  isSetting = 1;
  
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
  display_date_LCD(0, 0);

  switch(key)
  {
    case 'A':
      setTime();
      break;
    case 'C':
      isSet = 0;
      break;
    default:
      //
      break;
  }
  delay(5000);
}
