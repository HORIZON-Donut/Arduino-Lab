#define LED0 32
#define LED1 33
#define LED2 25
#define LED3 26
#define SW3_1 34
#define SW3_2 35
#define SW3_3 9

char disp_v[4] = {0, 0, 0, 0};
int count = 0;

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

void resetLED()
{
	for(int i = 0; i < 4; i++)
	{
		disp_v[i] = 0;
	}
}

void countBinary(int mode)
{
	if(mode)
	{
		count = (count - 1 + 16)%16;
	}
	else
	{
		count = (count + 1)%16;
	}

	for(char i = 0; i < 7; i++)
	{
		disp_v[i] = (count >> i) & 1;
	}
}

void lightRun(int mode)
{
	resetLED();
	if(mode)
	{
		count = (count - 1 + 4)%4;
	}
	else
	{
		count = (count + 1)%4;
	}
	disp_v[count] = ~disp_v[count];
}

void ledWrite()
{
	digitalWrite(LED0, disp_v[0]);
	digitalWrite(LED1, disp_v[1]);
	digitalWrite(LED2, disp_v[2]);
	digitalWrite(LED3, disp_v[3]);
}

void loop()
{
	int st1 = digitalRead(SW3_1);
	int st2 = digitalRead(SW3_2);

	if(st1)
	{	
		lightRun(st2);
	}
	else
	{
		countBinary(st2);
	}

	ledWrite();
	delay(1000);
}
