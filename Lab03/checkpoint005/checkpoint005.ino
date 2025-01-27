#include "DHT.h"

#define DHTPIN 21
#define DHTTYPE DHT11
//#define DHTTYPE DHT22
//#define DHTTYPE DHT21

DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600);
	Serial.println("DHT11, test!");
	dht.begin();
}

void loop() {
	delay(2000);
	
	float h = dht.readHumidity();
	float t = dht.readTemperature();
	float f = dht.readTemperature(true);

	if (isnan(h) || isnan(t) || isnan(f))
	{
		Serial.println("Fail to read from DHT sensor!");
		return;
	}

	Serial.print("Humidity: ");
	Serial.print(h);
	Serial.print("%\t");
	Serial.print("Temperature: ");
	Serial.print(t);
	Serial.print(" *C ");
	Serial.print(f);
	Serial.print(" *F\t");
}
