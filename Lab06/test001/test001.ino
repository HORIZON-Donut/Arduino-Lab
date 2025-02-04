#include <Wire.h> 
#include "RTClib.h" 
 
RTC_DS1307 rtc; 
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", 
"Saturday"}; 
DateTime now; 
 
void setup ()  
{ 
  Serial.begin(9600); 
  delay(3000); // wait for console opening 
 
  if (! rtc.begin()) { 
    Serial.println("Couldn't find RTC"); 
    while (1); 
  } 
 
  if (!rtc.isrunning()) { 
    Serial.println("RTC lost power, lets set the time!"); 
   
  // Comment out below lines once you set the date & time. 
    // Following line sets the RTC to the date & time this sketch was compiled 
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
   
    // Following line sets the RTC with an explicit date & time 
    // for example to set January 27 2017 at 12:56 you would call: 
     rtc.adjust(DateTime(2025, 2, 4, 13, 56, 0)); 
  } 
} 
 
void display_date_serial_monitor(void) 
{ 
    now = rtc.now(); 
    Serial.println("Current Date & Time: "); 
    Serial.print(now.year(), DEC);     
    Serial.print('/'); 
    Serial.print(now.month(), DEC);     
    Serial.print('/'); 
    Serial.print(now.day(), DEC); 
    Serial.print(" ("); 
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") "); 
    Serial.print(now.hour(), DEC); 
    Serial.print(':'); 
    Serial.print(now.minute(), DEC); 
    Serial.print(':'); 
    Serial.print(now.second(), DEC); 
    Serial.println(); 
    Serial.println(); 
} 
 
void loop ()  
{ 
    display_date_serial_monitor(); 
    delay(5000); 
}
