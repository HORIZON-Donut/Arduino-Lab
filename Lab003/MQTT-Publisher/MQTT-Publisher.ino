#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "HORIZON-Donut";
const char* password = "20040723";

// ThingSpeak MQTT settings
const char* mqtt_server = "mqtt.thingspeak.com";
const int mqtt_port = 1883;
const char* mqtt_user = "NjEeOww2Mwk4Jgk6NSs1ACA";
const char* mqtt_pass = "0tLxmHBOpGzmDJeiuGh/B0ot";
const char* mqtt_client_id = "NjEeOww2Mwk4Jgk6NSs1ACA";
const char* mqtt_topic = "channels/2860416/publish/INOHK3QWRWJW4223";
const char* subscribe_topic = "channels/2860416/subscribe/MYRPM7AENBOAYJJZ";
WiFiClient espClient;
PubSubClient client(espClient);

// Callback function to handle incoming messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  
  // Print the message payload
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected!");

  // Connect to the MQTT broker
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect(mqtt_client_id, mqtt_user, mqtt_pass)) {
      Serial.println("Connected to MQTT!");
      
      // Subscribe to the ThingSpeak channel for receiving data
      client.subscribe(subscribe_topic);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying...");
      delay(2000);
    }
  }
}

void loop() {
  // Publish data to ThingSpeak
  String payload = "hall = " + hallRead();  // data for field1
  if (client.publish(mqtt_topic, payload.c_str())) {
    Serial.println("Data published to ThingSpeak: " + payload);
  } else {
    Serial.println("Failed to publish data.");
  }
  
  // Call client.loop to keep listening for messages
  client.loop();
  
  delay(15000);  // Publish every 15 seconds
}
