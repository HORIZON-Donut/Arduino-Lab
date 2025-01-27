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

void display_1()
{
	digitalWrite(SegA, LOW);
	digitalWrite(SegB, HIGH);
	digitalWrite(SegC, HIGH);
	digitalWrite(SegD, LOW);
	digitalWrite(SegE, LOW);
	digitalWrite(SegF, LOW);
	digitalWrite(SegG, LOW);
}

void display_2()
{
	digitalWrite(SegA, HIGH);
	digitalWrite(SegB, HIGH);
	digitalWrite(SegC, LOW);
	digitalWrite(SegD, HIGH);
	digitalWrite(SegE, HIGH);
	digitalWrite(SegF, LOW);
	digitalWrite(SegG, HIGH);
}

void display_3()
{
	digitalWrite(SegA, HIGH);
	digitalWrite(SegB, HIGH);
	digitalWrite(SegC, HIGH);
	digitalWrite(SegD, HIGH);
	digitalWrite(SegE, LOW);
	digitalWrite(SegF, LOW);
	digitalWrite(SegG, HIGH);
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

	digitalWrite(digit10, HIGH);
}

void loop() {
	display_1();
	delay(1000);
	display_2();
	delay(1000);
	display_3();
	delay(1000);
}
