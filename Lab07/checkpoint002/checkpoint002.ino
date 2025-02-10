#define SegA 4 
#define SegB 0 
#define SegC 17 
#define SegD 16 
#define SegE 23 
#define SegF 19 
#define SegG 18 
#define DP 5 
#define ActivateD10 14 
#define ActivateD01 27 
//------------------------------- 
char BIN_TO_7SEGMENT2 (char A) 
{ 
 static char LOOKUPTB[ ] = 
 { 
 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 
 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 
 }; 
 return LOOKUPTB[A]; 
} 
void display7segment(char data) 
{ 
 (data & 0x01) ? digitalWrite(SegA, HIGH) : digitalWrite(SegA, LOW); 
 (data & 0x02) ? digitalWrite(SegB, HIGH) : digitalWrite(SegB, LOW); 
 (data & 0x04) ? digitalWrite(SegC, HIGH) : digitalWrite(SegC, LOW); 
 (data & 0x08) ? digitalWrite(SegD, HIGH) : digitalWrite(SegD, LOW); 
 (data & 0x10) ? digitalWrite(SegE, HIGH) : digitalWrite(SegE, LOW); 
 (data & 0x20) ? digitalWrite(SegF, HIGH) : digitalWrite(SegF, LOW); 
 (data & 0x40) ? digitalWrite(SegG, HIGH) : digitalWrite(SegG, LOW); 
} 
#include "driver/rtc_io.h" 
#define USE_EXT0_WAKEUP 1 // 1 = EXT0 wakeup, 0 = EXT1 wakeup 
#define WAKEUP_GPIO GPIO_NUM_34 
RTC_DATA_ATTR int bootCount = 0; 
void setup() { 
 pinMode(SegA, OUTPUT); 
 pinMode(SegB , OUTPUT); 
 pinMode(SegC , OUTPUT); 
 pinMode(SegD , OUTPUT); 
 pinMode(SegE , OUTPUT); 
 pinMode(SegF , OUTPUT); 
 pinMode(SegG , OUTPUT); 
 pinMode(DP, OUTPUT); 
 pinMode(ActivateD10, OUTPUT); 
 pinMode(ActivateD01, OUTPUT); 
 pinMode(WAKEUP_GPIO, INPUT); 
 Serial.begin(115200); 
 delay(1000); 
 ++bootCount; 
 Serial.println("Boot number: " + String(bootCount)); 
 delay(3000); 
 esp_sleep_enable_ext0_wakeup(WAKEUP_GPIO, 1);//wake up using high trigger 
 digitalWrite(ActivateD01, HIGH); 
 digitalWrite(ActivateD10, LOW); 
} 
void loop() { 
 int x, tmp; 
 x = digitalRead(GPIO_NUM_34); 
 if (x == 0) 
 { 
 Serial.println("Going to sleep now"); 
 delay(300); 
 esp_deep_sleep_start(); 
 } 
 else 
 { 
 tmp = BIN_TO_7SEGMENT2(1); 
 display7segment(tmp); 
 Serial.println("The CPU is running"); 
 delay(1000); 
 } 
} 
//---E:\001_teaching\241-102 Micro and Digital for 
//AI\projects_ESP32\goto_deep_sleep_wakup_with_SW3_1\ 
