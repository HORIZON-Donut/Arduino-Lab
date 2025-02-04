#include <Wire.h> 

#include "RTClib.h" 
 
RTC_DS1307 rtc; 
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
    rtc.adjust(DateTime(2025, 2, 4, 13, 56, 0)); 
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
 
void loop ()  
{ 
    display_date_serial_monitor(); 
    delay(5000); 
}
