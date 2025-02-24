#define ADC0_pin 36
#define ADC1_pin 39

int adc01Val;
int adc02Val;

void setup() {
	Serial.begin(9600);
}

void loop() {
	adc01Val = analogRead(ADC0_pin);

	Serial.print("ADC0 Value = ");
	Serial.println(adc01Val);

	delay(300);
}
