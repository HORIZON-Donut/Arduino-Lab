#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 15, 16, 17, 4, 0);

const int trigPin = 21; //เชื่อมต่อขา Trig เข้ากับขา GPIO21(SDA) ของบอร์ด ESP32
const int echoPin = 22; //เชื่อมต่อขา Echo เข้ากับขา GPIO22(SCL) ของบอร์ด ESP32
long duration;
int distance;
void setup()
{
 lcd.begin(16, 2);
 lcd.clear();
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}
void loop()
{
 digitalWrite(trigPin, LOW); //เคลียร์สัญญาณ Trig
 delayMicroseconds(2); //ให้สัญญาณ Trig เป็นลอจิก LOW เป็นเวลา 2 ไมโครวินาที
 digitalWrite(trigPin, HIGH); //ส่งสัญญาณ Trig ให้เป็นลอจิก HIGH
 delayMicroseconds(10); //ให้สัญญาณ Trig เป็นลอจิก HIGH เป็นเวลา 10 ไมโครวินาที
 digitalWrite(trigPin, LOW); //หยุดส่งสัญญาณ Trig
 duration = pulseIn(echoPin, HIGH); //วัดความกว้างของพัลส์ที่ขา Echo ว่ามีลอจิก HIGH ยาวเท่าใด
 distance= duration*0.034/2; //คำนวณค่าระยะห่าง
 Serial.print("Distance: ");
 Serial.println(distance);
 lcd.setCursor(2, 0);
 lcd.print("Distance");
 lcd.setCursor(1, 1);
 lcd.print(">>> ");
 lcd.print(distance);
 delay(1000);
}
