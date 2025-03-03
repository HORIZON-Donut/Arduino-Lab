#include <PubSubClient.h>

// WiFi-Verbindung
const char* ssid = "HORIZON-Donut";
const char* password = "20040723";
WiFiClient wifiClient;

// MQTT-Verbindung
const char* mqtt_server = "mqtt3.thingspeak.com";
const char* mqtt_username = "NjEeOww2Mwk4Jgk6NSs1ACA";
const char* mqtt_password = "0tLxmHBOpGzmDJeiuGh/B0ot";
const char* mqtt_id = "2862145";
const char* topic = "channels/2862145/publish/INOHK3QWRWJW4223";
//PubSubClient client(wifiClient);

PubSubClient client(mqtt_server, 1883, wifiClient);

// BMP180-Sensor
Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // WLAN verbinden
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // MQTT-Verbindung
  client.setServer(mqtt_server, 1883);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT Broker...");
    if (client.connect(mqtt_id, mqtt_username, mqtt_password )) {
      Serial.println("Connected to MQTT Broker");
    } else {
      Serial.print("Failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
  
  // BMP180 initialisieren
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }
}

void loop() {
  // Temperatur auslesen
  float hall = hallRead();

  // Temperatur über MQTT veröffentlichen
  String payload = String("field1=") + String(hall);
  client.publish(topic, payload.c_str());
mqttPublish 
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  delay(10000); // 10 Sekunden warten
}