#define ADC0_pin 36
#define ADC1_pin 39
#define SegA 4
#define SegB 0
#define SegC 17
#define SegD 16
#define SegE 23
#define SegF 19
#define SegG 18
#define DP 5
#define digit10 14
#define digit01 27

#define s1 3826
#define s2 3376
#define s3 2789
#define s4 2047
#define s5 1309

int adcVal;
int shifting;
int Digit01;
int Digit10;

float voltage;


//-----------------------------------
char BIN_TO_7SEGMENT2(char A)
{
	static char LOOKUPTB[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

	return LOOKUPTB[A];
}

void display7segment(char data)
{
	(data & 0x01)? digitalWrite(SegA, HIGH):digitalWrite(SegA, LOW);
	(data & 0x02)? digitalWrite(SegB, HIGH):digitalWrite(SegB, LOW);
	(data & 0x04)? digitalWrite(SegC, HIGH):digitalWrite(SegC, LOW);
	(data & 0x08)? digitalWrite(SegD, HIGH):digitalWrite(SegD, LOW);
	(data & 0x10)? digitalWrite(SegE, HIGH):digitalWrite(SegE, LOW);
	(data & 0x20)? digitalWrite(SegF, HIGH):digitalWrite(SegF, LOW);
	(data & 0x40)? digitalWrite(SegG, HIGH):digitalWrite(SegG, LOW);

}

void setup() {
	pinMode(SegA, OUTPUT);
	pinMode(SegB, OUTPUT);
	pinMode(SegC, OUTPUT);
	pinMode(SegD, OUTPUT);	
	pinMode(SegE, OUTPUT);
	pinMode(SegF, OUTPUT);
	pinMode(SegG, OUTPUT);
	pinMode(DP, OUTPUT);
	pinMode(digit10, OUTPUT);
	pinMode(digit01, OUTPUT);

	Serial.begin(115200);

	Digit01 = 0;
	Digit10 = 0;
	shifting = 200;
}

int PushSwitch(int n)
{
	int sw;

	if (n < s1 + shifting && n > s1 - shifting)
		sw = 0;
	
	else if (n < s2 + shifting && n > s2 - shifting)
		sw = 1;
	
	else if (n < s3 + shifting && n > s3 - shifting)
		sw = 2;
	
	else if (n < s4 + shifting && n > s4 - shifting)
		sw = 3;
	
	else if (n < s5 + shifting && n > s5 - shifting)
		sw = 4;
	
	else
		sw = 5;

	return sw;
}

void countDec(char mode)
{
	if(mode == 1)
	{
		Digit01++;
		if(Digit01 > 9) {Digit10++; Digit01 = 0;}
	}
	else if (mode == 0)
	{
		Digit01--;
		if(Digit01 < 0) {Digit10--; Digit01 = 9;}
	}

  Digit01 = (Digit01 + 10) % 10;
  Digit10 = (Digit10 + 10) % 10;
}


void loop() {
	adcVal = analogRead(ADC0_pin);
	voltage = (adcVal / 4095.00) * 3.3;

	switch(PushSwitch(voltage))
	{
		case 0:
			countDec(1);
			break;

		case 1:
			countDec(0);
			break;

		case 2:
			Digit10++;
			countDec(-1);
			break;

		case 3:
			Digit01++;
			countDec(-1);
			break;

		case 4:
			Digit01 = 0;
			Digit10 = 0;
			break;

		default:
			break;
	}

	delay(300);
}
