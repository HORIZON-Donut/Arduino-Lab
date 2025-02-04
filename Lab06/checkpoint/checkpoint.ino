#include <Wire.h>
#include <LiquidCrystal.h>

#include "RTClib.h" 

RTC_DS1307 rtc; 
char daysOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; 
DateTime now;

LiquidCrystal lcd(2, 15, 17, 16, 4, 0);
void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("Start up");
  delay(3000);

  lcd.setCursor(3, 1);
  if (! rtc.begin()) {
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Can't find RTC"); 
    while (1); 
  } 
 
  if (!rtc.isrunning()) {
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("RTC lost power");
    lcd.setCursor(1, 0);
    lcd.print("lets set time!"); 
   
  // Comment out below lines once you set the date & time. 
    // Following line sets the RTC to the date & time this sketch was compiled 
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
   
    // Following line sets the RTC with an explicit date & time 
    // for example to set January 27 2017 at 12:56 you would call: 
     rtc.adjust(DateTime(2025, 2, 4, 13, 56, 0)); 
  }

  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set up completed");
}

void display_date_serial_monitor(void) 
{
  lcd.clear();
  lcd.setCursor(1, 0);
  now = rtc.now();
  lcd.print(now.year(), DEC);     
  lcd.print('/'); 
  lcd.print(now.month(), DEC);     
  lcd.print('/'); 
  lcd.print(now.day(), DEC);  
  lcd.print(':');
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.setCursor(2, 0);
  lcd.print(now.hour(), DEC); 
  lcd.print(':'); 
  lcd.print(now.minute(), DEC); 
  lcd.print(':'); 
  lcd.print(now.second(), DEC); 
} 

void loop() {
  display_date_sserial_monitor();
  delay(100);
}
