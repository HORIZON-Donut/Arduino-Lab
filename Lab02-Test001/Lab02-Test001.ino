#define LED0 32
#define LED1 33
#define LED2 25
#define LED3 26

void setup() {
  // put your setup code here, to run once:
	pinMode(LED0, OUTPUT);
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
	digitalWrite(LED0, HIGH);
	digitalWrite(LED1, HIGH);
	digitalWrite(LED2, HIGH);
	digitalWrite(LED3, HIGH);
	
	delay(1000);	//1000 ms
	digitalWrite(LED0, LOW);
	digitalWrite(LED1, LOW);
	digitalWrite(LED2, LOW);
	digitalWrite(LED3, LOW);
	
	delay(1000);
}
