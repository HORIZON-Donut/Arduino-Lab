#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include "RTClib.h"
#include <map>
#include <LiquidCrystal.h>
 // RS E D4 D5 D6 D7
LiquidCrystal lcd1( 2, 15, 17, 16, 4, 0 );

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
"Saturday"};
DateTime now;

#define BUZZER_PIN 12
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
Keypad_I2C keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR);
void I2C_bus_scan(void);

int h = 0;
int m = 0;
int alarm_time = 0;
int a = 0;
int state = 0;
int set_time = 0;
unsigned long previousMillis = 0;
const long interval = 500;
std::map<char, int> num = {
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9}
};

void setup(){
 Wire.begin( );
 keypad.begin( );
 Serial.begin(38400);
 I2C_bus_scan();
 lcd1.begin(16, 2); // จอกว้าง 16 ตัวอักษร 2 บรรทัด
 lcd1.clear(); // ล้างหน้าจอ

 if (! rtc.begin()) {
 Serial.println("Couldn't find RTC");
 while (1);
 }
 if (!rtc.isrunning()) {
 Serial.println("RTC lost power, lets set the time!");

 // Comment out below lines once you set the date & time.
 // Following line sets the RTC to the date & time this sketch was compiled
 // rtc.adjust(DateTime(F(_DATE_), F(_TIME_))); 

 // Following line sets the RTC with an explicit date & time
 // for example to set January 27 2017 at 12:56 you would call:
 // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
 }
}

void loop(){
 char key = keypad.getKey();
 now = rtc.now();
//  int c_h = now.hour();
//  int c_m = now.minute();

 show_time();

 if (key != NO_KEY){
 Serial.print(key);
 Serial.println(" is pressed");
 }

 if (key == 'A') {
  a = 0;
  state = 0;
  set_time = 1;
  while(set_time) {
    while (a == 0) {
      unsigned long currentMillis = millis();
      key = keypad.getKey();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if (state == 0) {
          notime_11();
        }
        else if (state == 1) {
          notime_12();
        }
        }
      else if (currentMillis - previousMillis >= interval / 2) {
        show_time();
      }
      
      if (key >= '0' && key <= '2' && state == 0) {
        h = h % 10 + num[key] * 10;
        state = 1;
      }
      else if (key >= '0' && key <= '3' && state == 1 && h / 10 == 2) {
        h = ((h / 10) % 10) * 10 + num[key];
        state = 0;
      }
      else if (key >= '0' && key <= '9' && state == 1 && h / 10 != 2) {
        h = ((h / 10) % 10) * 10 + num[key];
        state = 0;
      }
      else if (key == 'A') {
        a = 1;
        state = 0;
      }
      else if (key == '#') {
        alarm_time = 1;
        set_time = 0;
        break;
      }
    }
    while (a == 1) {
      // a = (a > 1) ? 0 : a;
      unsigned long currentMillis = millis();
      key = keypad.getKey();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if (state == 0) {
          notime_21();
        }
        else if (state == 1) {
          notime_22();
        }
        }
      else if (currentMillis - previousMillis >= interval / 2) {
        show_time();
      }
      
      if (key >= '0' && key <= '5' && state == 0) {
        m = m % 10 + num[key] * 10;
        state = 1;
      }
      else if (key >= '0' && key <= '9' && state == 1) {
        m = ((m / 10) % 10) * 10 + num[key];
        state = 0;
      }
      else if (key == 'A') {
        a = 0;
        state = 0;
      }
      else if (key == '#') {
        alarm_time = 1;
        set_time = 0;
        break;
      }
    }
  }
 }

 else if (key == 'C' && alarm_time == 1) {
  alarm_time = 0;
 }

  else if (key == 'C' && alarm_time == 0) {
  alarm_time = 1;
 }

 else if (now.hour() == h && now.minute() == m && alarm_time == 1) {
  while (true) {
    unsigned long currentMillis = millis();
    key = keypad.getKey();
    if (currentMillis - previousMillis >= interval * 2) {
      previousMillis = currentMillis;
      lcd1.clear();
      noTone(BUZZER_PIN);
      }
    else if (currentMillis - previousMillis >= interval) {
      show_time();
      tone(BUZZER_PIN, 1000, 500);
    }

    if (key != NO_KEY && key != 'A' && key != 'C') {
      alarm_time = 0;
      noTone(BUZZER_PIN); 
      break;
    }
  }
 }
}

void I2C_bus_scan(void)
{
 Serial.println ();
 Serial.println ("www.9arduino.com ...");
 Serial.println ("I2C scanner. Scanning ...");
 byte count = 0;
 Wire.begin();
 for (byte i = 8; i < 120; i++) // Loop ค้นหา Address
 {
 Wire.beginTransmission (i);
 if (Wire.endTransmission () == 0)
 {
 Serial.print ("Found address: ");
 Serial.print (i, DEC);
 Serial.print (" (0x");
 Serial.print (i, HEX);
 Serial.println (")");
 count++;
 delay (1);
 }
 }
 Serial.println ("Done.");
 Serial.print ("Found ");
 Serial.print (count, DEC);
 Serial.println (" device(s).");
}

void show_time(void) {
 now = rtc.now();
 char timeStr[6];

 lcd1.clear();
 lcd1.setCursor(0, 0);
 lcd1.print("Current ");
 sprintf(timeStr, "%02d:%02d", now.hour(), now.minute());
 lcd1.print(timeStr);

 lcd1.setCursor(0, 1);
 lcd1.print("Alarm   ");
 sprintf(timeStr, "%02d:%02d", h, m);
 lcd1.print(timeStr);
 lcd1.setCursor(14, 1);
 if (alarm_time == 1) {
  lcd1.print("on");
 }
 else if (alarm_time == 0) {
  lcd1.print("off");
 }
}

void notime_11(void) {
 now = rtc.now();
 char timeStr[6];

 lcd1.clear();
 lcd1.setCursor(0, 0);
 lcd1.print("Current ");
 sprintf(timeStr, "%02d:%02d", now.hour(), now.minute());
 lcd1.print(timeStr);

 lcd1.setCursor(0, 1);
 lcd1.print("Alarm   ");
 sprintf(timeStr, " %d:%02d", h % 10, m);
 lcd1.print(timeStr);
 lcd1.setCursor(14, 1);
 if (alarm_time == 1) {
  lcd1.print("on");
 }
 else if (alarm_time == 0) {
  lcd1.print("of");
 }
}

void notime_12(void) {
 now = rtc.now();
 char timeStr[6];

 lcd1.clear();
 lcd1.setCursor(0, 0);
 lcd1.print("Current ");
 sprintf(timeStr, "%02d:%02d", now.hour(), now.minute());
 lcd1.print(timeStr);

 lcd1.setCursor(0, 1);
 lcd1.print("Alarm   ");
 sprintf(timeStr, "%d :%02d", h / 10, m);
 lcd1.print(timeStr);
 lcd1.setCursor(14, 1);
 if (alarm_time == 1) {
  lcd1.print("on");
 }
 else if (alarm_time == 0) {
  lcd1.print("of");
 }
}

void notime_21(void) {
 now = rtc.now();
 char timeStr[6];

 lcd1.clear();
 lcd1.setCursor(0, 0);
 lcd1.print("Current ");
 sprintf(timeStr, "%02d:%02d", now.hour(), now.minute());
 lcd1.print(timeStr);

 lcd1.setCursor(0, 1);
 lcd1.print("Alarm   ");
 sprintf(timeStr, "%02d: %d", h, m % 10);
 lcd1.print(timeStr);
 lcd1.setCursor(14, 1);
 if (alarm_time == 1) {
  lcd1.print("on");
 }
 else if (alarm_time == 0) {
  lcd1.print("of");
 }
}

void notime_22(void) {
 now = rtc.now();
 char timeStr[6];

 lcd1.clear();
 lcd1.setCursor(0, 0);
 lcd1.print("Current ");
 sprintf(timeStr, "%02d:%02d", now.hour(), now.minute());
 lcd1.print(timeStr);

 lcd1.setCursor(0, 1);
 lcd1.print("Alarm   ");
 sprintf(timeStr, "%02d:%d ", h, m / 10);
 lcd1.print(timeStr);
 lcd1.setCursor(14, 1);
 if (alarm_time == 1) {
  lcd1.print("on");
 }
 else if (alarm_time == 0) {
  lcd1.print("of");
 }
}
