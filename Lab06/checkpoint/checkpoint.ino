#include <Wire.h> 
#include <LiquidCrystal.h>

#include "RTClib.h" 

LiquidCrystal lcd(2, 15, 17, 16, 4, 0); 
RTC_DS1307 rtc; 
DateTime now; 

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

void setup ()  
{
  lcd.begin(16, 2);
  lcd.clear();
  
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
    display_date_serial_monitor(); 
    delay(5000); 
}
