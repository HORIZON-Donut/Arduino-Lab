#include <WiFi.h>

WiFiClient  client;
const int LED=32;
const char *ssid = “XXXXX";
const char *password = “YYYYY";

void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  WiFi.mode(WIFI_STA);  
  
  Serial.println("Connecting Wifi...");
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi not CONNECTED");    
    delay(1000);
  }
  digitalWrite(LED,LOW);    
  
}
void loop()
{
  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());    
    digitalWrite(LED,!digitalRead(LED));  
  }
  delay(1000);  
}