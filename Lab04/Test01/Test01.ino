#define ADC0_pin 36
#define ADC1_pin 39

int adcVal;
float voltage;

void setup() {
	Serial.begin(115200);
}

void loop() {
	adcVal = analogRead(ADC0_pin);
	voltage = (adcVal / 4095.00) * 3.3;
	Serial.print("Value = ");
	Serial.print(adcVal);
	Serial.print("		Voltage = ");
	Serial.println(voltage);
	Serial.println(" V");
	delay(1000);
}
