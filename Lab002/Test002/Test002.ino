const int DG[2]={27,14};
const int segMentPin[7]={4,0,17,16,23,19,18};
const int dot=20;
int i;
int digit=0;   
hw_timer_t * timer = NULL;  /* create a hardware timer */

void IRAM_ATTR onTimer(){
  if(digit==0){
    digitalWrite(DG[0],LOW);
    digitalWrite(DG[1],HIGH);
    digit=1;
  }
  else
  {
    digitalWrite(DG[1],LOW);
    digitalWrite(DG[0],HIGH);
    digit=0;    
  }
}

void setup() {
   timer = timerBegin(0, 80, true);
   timerAttachInterrupt(timer, &onTimer, true);
   timerAlarmWrite(timer, 1000000, true);
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