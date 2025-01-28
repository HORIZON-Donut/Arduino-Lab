int soundPin = 21;
int ledPin = 13;
unsigned long previous_time = 0;

bool check_clap()
{
	static unsigned long current_time = 0;
	char = sw;
	sw = digitalRead(soundPin);
	if(sw)
	{
		return false;
	}
	else
	{
		current_time = millis();
		if((current_time - previous_time) > 25)
		{
			previous_time = millis();
			return true;
		}
		else
		{
			previous_time = millis();
			return false;
		}
	}
}

int val;
int state;
int num_clap;

void setup() {
	pinMode(ledPin, OUTPUT);
	pinMode(soundPin, INPUT);
	Serial.begin(9600);
	state = 0;
	num_clap = 0;
	Serial.println("num_clap = 0");
}

void loop() {
	val = check_clap;
	if(val == true)
	{
		Serial.print("Clap detected!!! #");
		Serial.print(num_clap);
		num_clap++;

		if(state == 1)
		{
			state = 0;
			Serial.println("	LED is turned off");
		}
		else
		{
			state = 1;
			Serial.println("	LED is trned on");
		}
	}

	if(state == 1)
		digitalWrite(ledPin, LOW);
	else
		digitalWrite(ledPin, HIGH);
}
