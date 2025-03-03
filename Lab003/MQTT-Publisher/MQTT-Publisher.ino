#include <WiFi.h>
//#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#define BUILTIN_LED 32
// Update these with values suitable for your network.

const char* ssid = "HORIZON-Donut";
const char* password = "2004723";


const char* mqtt_broker = "re065841.ala.dedicated.aws.emqxcloud.com";
const char *topic = "Hall data";
const char *mqtt_username = "6510110608";
const char *mqtt_password = "1234567890";
const int mqtt_port = "XXXX";
String client_id = "6510110608";

WiFiClient espClient;
//WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup() {
 // Set software serial baud to 115200;
 Serial.begin(115200);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 Serial.println("");
 Serial.print("Connecting to WiFi ");
 while (WiFi.status() != WL_CONNECTED) {
     Serial.print(".");
     delay(500);     
 }
 Serial.println("");
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
  
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.println(client.state());
         delay(2000);
     }
 }
 // publish and subscribe
 client.publish(topic, "Hi EMQ X I'm ESP32 ^^");
 client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------");
}

void loop() {
 client.loop();
 delay(5000);
  if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
         client.subscribe("outTopic");
         client.subscribe("inTopic");
         client.subscribe("Hello MQTT");
  } 
  else {
         Serial.print("failed with state ");
         Serial.println(client.state());
         delay(2000);
  }
}
