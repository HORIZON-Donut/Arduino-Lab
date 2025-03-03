#include <WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

WiFiClient  client;
const int LED=32;
const char *ssid = "HORIZON-Donut";
const char *password = "20040723";
unsigned long myChannelNumber = 2860416;
const char * myReadAPIKey = "IWZMTSVHYXTXM4G2";

void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  WiFi.begin(ssid,password);
  Serial.println("Connecting Wifi...");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi not CONNECTED");
    delay(500);
  }
  digitalWrite(LED,LOW);    
  Serial.println ("Wifi CONNECTED");
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED,!digitalRead(LED));    
    long field01 = ThingSpeak.readLongField(myChannelNumber, 1, myReadAPIKey);
    long field10 = ThingSpeak.readLongField(myChannelNumber, 2, myReadAPIKey);
    Serial.print("Feild 01: ");
    Serial.println(feild01);
    Serial.print("Feild 10: ");
    Serial.println(feild10);
  else
  { digitalWrite(LED,HIGH);
  }  
  delay(15000);
}
