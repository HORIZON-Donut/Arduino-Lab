const int DG[2]={27,14};
const int segMentPin[7]={4,0,17,16,23,19,18};
const int dot=20;
int i;
int digit=0;   
int num=0;
bool segMent[10][7]={1,1,1,1,1,1,0,
                     0,1,1,0,0,0,0,
                     1,1,0,1,1,0,1,
                     1,1,1,1,0,0,1,
                     0,1,1,0,0,1,1,
                     1,0,1,1,0,1,1,
                     1,0,1,1,1,1,1,
                     1,1,1,0,0,0,0,
                     1,1,1,1,1,1,1,
                     1,1,1,1,0,1,1};


hw_timer_t * timer = NULL;  /* create a hardware timer */
hw_timer_t * countTime = NULL;
void IRAM_ATTR onTimer(){
  if(digit==0){
    digitalWrite(DG[0],LOW);
    for(i=0;i<7;i++)
    {
      digitalWrite(segMentPin[i],segMent[num][i]);
    }
    digitalWrite(DG[1],HIGH);
    digit=1;
  }
  else
  {
    digitalWrite(DG[1],LOW);
    for(i=0;i<7;i++)
    {
      digitalWrite(segMentPin[i],segMent[num+1][i]);
    }
    digitalWrite(DG[0],HIGH);
    digit=0;    
  }
  
}
void IRAM_ATTR counting(){
  num=(num<8?num+1:0);
}
void setup() {
   timer = timerBegin(0, 80, true);   //Timer number 0
   timerAttachInterrupt(timer, &onTimer, true);
   timerAlarmWrite(timer, 1000000/30/2, true);
   timerAlarmEnable(timer);

   countTime = timerBegin(1,80,true);  //Timer number 1
   timerAttachInterrupt(countTime, &counting, true);
   timerAlarmWrite(countTime, 1000000, true);
   timerAlarmEnable(countTime);
   
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