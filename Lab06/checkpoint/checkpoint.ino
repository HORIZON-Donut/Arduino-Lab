#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad_I2C.h> 
#include <Keypad.h> 

#include "RTClib.h" 

#define I2CADDR 0x20 

const byte ROWS = 4; 
const byte COLS = 4; 
 
char hexaKeys[ROWS][COLS] = { 
  {'1','2','3','A'}, 
  {'4','5','6','B'}, 
  {'7','8','9','C'}, 
  {'*','0','#','D'} 
}; 
byte rowPins[ROWS] = {7, 6, 5, 4}; 
byte colPins[COLS] = {3, 2, 1, 0}; 

RTC_DS1307 rtc; 
Keypad_I2C keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 
char daysOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; 
DateTime now;

//Prototype function
void I2C_bus_scan(void); 

LiquidCrystal lcd(2, 15, 17, 16, 4, 0);
void setup() {
  
  Wire.begin();
  keypad.begin();
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
    
    rtc.adjust(DateTime(2025, 2, 4, 13, 56, 0)); 
  }

  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set up I2C");

  delay(3000);
  I2C_bus_scan();
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

void I2C_bus_scan(void) 
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("www.9arduino.com");
  lcd.setCursor(0, 1); 
  lcd.print("Scanning ..."); 
  byte count = 0; 
 
  Wire.begin(); 
  for (byte i = 8; i < 120; i++)  // Loop คนหา Address  
  { 
    Wire.beginTransmission (i); 
    if (Wire.endTransmission () == 0) 
      {
        lcd.clear();
        lcd.setCursor(0, 0); 
        lcd.print ("Found address: ");
        lcd.setCursor(1, 1); 
        lcd.print (i, DEC); 
        lcd.print (" (0x"); 
        lcd.print (i, HEX); 
        lcd.println (")"); 
        
        count++; 
        delay (1);  
      }  
  }
  lcd.clear()
  lcd.setCursor(2, 0);
  lcd.print("Done."); 
  lcd.setCursor(1, 1);
  lcd.print ("Found "); 
  lcd.print(count, DEC); 
  lcd.print(" device(s)."); 
}   
