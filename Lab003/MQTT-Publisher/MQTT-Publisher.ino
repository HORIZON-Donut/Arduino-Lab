#include <WiFi.h>
#include <PubSubClient.h>

// Replace with your own credentials
const char* ssid = "HORIZON-Donut";  // WiFi SSID
const char* password = "20040723";  // WiFi Password

// ThingSpeak MQTT settings
const char* mqtt_server = "mqtt.thingspeak.com";
const int mqtt_port = 1883;
const char* mqtt_user = "YourThingSpeakAPIKey";  // Replace with your ThingSpeak API Key
const char* mqtt_pass = "";  // No password needed
const char* mqtt_client_id = "ESP32Client";  // Unique client ID
const char* mqtt_topic = "channels/2860416/publish/YOUR_WRITE_API_KEY";  // Topic to publish to (replace with your API Key)
const char* subscribe_topic = "channels/2860416/subscribe/YOUR_READ_API_KEY";  // Topic to subscribe to (replace with your API Key)

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
  String payload = "field1=" + String(random(0, 1024));  // Random data for field1
  if (client.publish(mqtt_topic, payload.c_str())) {
    Serial.println("Data published to ThingSpeak: " + payload);
  } else {
    Serial.println("Failed to publish data.");
  }
  
  // Call client.loop to keep listening for messages
  client.loop();
  
  delay(15000);  // Publish every 15 seconds
}
