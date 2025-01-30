int soundPin = 21; //ต่อกับ GPIO21 (หรือขา SDA) 
int ledPin = 13; //แสดงผลบน LED0 บนบอร์ด ESP32 Starter Kit 
unsigned long previous_time=0; 
bool check_clap() 
{ 
 static unsigned long current_time; 
 char sw; 
 sw = digitalRead(soundPin); 
 if (sw) 
 { 
 return false; 
 } 
 else 
 { 
 current_time = millis(); 
 if ((current_time-previous_time)>25) 
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
void setup() 
{ 
 pinMode(ledPin, OUTPUT); 
 pinMode(soundPin, INPUT); 
 Serial.begin (9600); 
 state =0; 
 num_clap = 0; 
 Serial.println("num_clap = 0"); 
}

void loop() 
{ 
 val = check_clap(); 
 if (val==true) 
 { 
 Serial.print("Clap deteected!!! #"); 
 Serial.print(num_clap); 
 num_clap++; 
 if (state ==1) 
 { 
 state =0; 
 Serial.println(" LED is turned off"); 
 } 
 else 
 { 
 state =1; 
 Serial.println(" LED is turned on"); 
 } 
 } 
 if (state ==1) 
 digitalWrite(ledPin, LOW); //turn LED1 on 
 else 
 digitalWrite(ledPin, HIGH); //turn LED1 off 
} 
