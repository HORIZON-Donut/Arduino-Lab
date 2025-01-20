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
#define SW3_1 34
#define SW3_2 35

char Digit01 = 0;
char Digit10 = 0;

//-----------------------------------
char BIN_TO_7SEGMENT2(char A)
{
	static char LOOKUPTB[] = {
		0x3F,
		0x06,
		0x5B,
		0x4F,
		0x66,
		0x6D,
		0x7D,
		0x07,
		0x7F,
		0x6F,
		0x77,
		0x7C,
		0x39,
		0x5E,
		0x79,
		0x71
	};

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

	pinMode(SW3_1, INPUT);
	pinMode(SW3_2, INPUT);
}

void Display()
{
	char disp_v = 0;

	char tmp01 = BIN_TO_7SEGMENT2(Digit01);
	char tmp10 = BIN_TO_7SEGMENT2(Digit10);

	for(char i = 0; i < 100; i++)
	{
		display7segment(tmp01);
		digitalWrite(digit01, HIGH);
		digitalWrite(digit10, LOW);
		delay(5);

		display7segment(tmp10);
		digitalWrite(digit01, LOW);
		digitalWrite(digit10, HIGH);
		delay(5);
	}
}

void countHex(char mode)
{
	if(mode)
	{
		Digit01++;
		if(Digit01 > 15){Digit10++; Digit01 = 0;}
	}
	else
	{
		Digit01--;
		if(Digit01 < 0) {Digit10--; Digit01 = 0;}
	}
}

void countDec(char mode)
{
	if(mode)
	{
		Digit01++;
		if(Digit01 > 9) {Digit10++; Digit01 = 0;}
	}
	else
	{
		Digit01--;
		if(Digit01 < 0) {Digit10--; Digit01 = 0;}
	}
}

void loop() {

	int st1 = digitalRead(SW3_1);
	int st2 = digitalRead(SW3_2);

	if(st1)
	{
		countHex(st2);
	}
	else
	{
		countDec(st2);
	}
	Display();
}
