const int ledPin = 32; /* LED pin */
const int ledChannel = 0;
const int resolution = 8;
const int freq = 5000;
const int maxDuty = 255; //2^resolution-1
void setup() {
  Serial.begin(115200);
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel); // attach the channel to the GPIO to be controlled
}

void loop() {
  for(int dutyCycle = 0; dutyCycle <= maxDuty; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    Serial.println(dutyCycle);
    delay(30);
  }
}