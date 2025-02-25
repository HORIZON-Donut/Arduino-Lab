const int DG[2]={27,14};
const int segMentPin[7]={4,0,17,16,23,19,18};
const int digit01[7] = {1, 1, 1, 1, 1, 1, 1};
const int digit10[7] = {1, 1, 1, 1, 1, 1, 0};
const int dot=20;
int i;
int digit=0;   

int fps = 120;

hw_timer_t * timer = NULL;  /* create a hardware timer */

void Display()
{
	const int* disp = (digit == 1) ? digit01:digit10;
	for(i = 0; i < 7; i++)
	{
		digitalWrite(segMentPin[i], (disp[i] == 1)? HIGH:LOW);
	}
}

void IRAM_ATTR onTimer(){
  if(digit==0){
    digitalWrite(DG[0],LOW);
    digitalWrite(DG[1],HIGH);
	Display();
    digit=1;
  }
  else
  {
    digitalWrite(DG[1],LOW);
    digitalWrite(DG[0],HIGH);
	Display();
    digit=0;    
  }
}

void setup() {
   timer = timerBegin(0, 80, true);
   timerAttachInterrupt(timer, &onTimer, true);
   timerAlarmWrite(timer, 1000000/fps/2, true);
   timerAlarmEnable(timer);
   
   for(i=0;i<2;i++){
    pinMode(DG[i],OUTPUT);   
    digitalWrite(DG[i],HIGH);
  }  
  for(i=0;i<7;i++)
  { pinMode(segMentPin[i],OUTPUT);
    digitalWrite(segMentPin[i],HIGH);
  }  
}

void loop() {  
}
