#include <Wire.h>
#include <LiquidCrystal.h>

#include "DHT.h"

#define DHTPIN 21
#define DHTTYPE DHT11
//#define DHTTYPE DHT22
//#define DHTTYPE DHT21

LiquidCrystal lcd1(2, 15, 17, 16, 4, 0);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd1.begin(16, 2);
  lcd1.clear();
	
  Serial.begin(9600);
  Serial.println("DHT11, test!");
  dht.begin();
}

void loop() {
	float h = dht.readHumidity();
	float t = dht.readTemperature();
	float f = dht.readTemperature(true);
	
	if (isnan(h) || isnan(t) || isnan(f))
	{
		lcd1.setCursor(1, 0);
		lcd1.print("Unable to read");
		return;
	}
	
  	lcd1.setCursor(1, 0); 
 	lcd1.print("Humidity: "); 
	lcd1.print(h);
	lcd1.print("%");
	
 	lcd1.setCursor(1, 1); 
  	lcd1.print("Temperature: ");
	lcd1.print(t):
	lcd1.print(" *C ");
	lcd1.print(f);
	lcd1.print(" *F");
	
	delay(1000);
  	lcd1.clear();
}
