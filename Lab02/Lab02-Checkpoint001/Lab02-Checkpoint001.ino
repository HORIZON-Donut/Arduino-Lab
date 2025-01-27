#define LED0 32
#define LED1 33
#define LED2 25
#define LED3 26
#define SW3_1 34
#define SW3_2 35
#define SW3_3 9

char disp_v = 0;

void setup() {
  // put your setup code here, to run once:
	pinMode(LED0, OUTPUT);
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(SW3_1, INPUT);
	pinMode(SW3_2, INPUT);
	pinMode(SW3_3, INPUT);
}

void loop() {
	
	int st = digitalRead(SW3_1);

	if(st)
	{
		digitalWrite(LED0, HIGH);
		digitalWrite(LED1, HIGH);
	}
	else
	{
		digitalWrite(LED0, LOW);
		digitalWrite(LED1, LOW);
	}

	digitalWrite(LED2, disp_v);
	disp_v = ~disp_v;

	delay(1000);
}
