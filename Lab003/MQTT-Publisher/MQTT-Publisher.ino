#include <WiFi.h>
#include <PubSubClient.h>

// WiFi & MQTT settings
const char* ssid = "HORIZON-Donut";
const char* password = "20040723"
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp32 analog data";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected!");

  client.setServer(mqtt_server, mqtt_port);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying...");
      delay(2000);
    }
  }
}

void loop() {
  int analogValue = hallRead();  // Read from analog pin 34
  char msg[10];
  sprintf(msg, "%d", analogValue);
  
  Serial.print("Publishing: ");
  Serial.println(msg);
  
  client.publish(mqtt_topic, msg);
  delay(2000);  // Publish every 2 seconds
}
