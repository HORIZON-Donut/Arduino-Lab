#include <Wire.h>

void I2C_bus_scan(void) 
{ 
  Serial.println (); 
  Serial.println ("www.9arduino.com ..."); 
  Serial.println ("I2C scanner. Scanning ..."); 
  byte count = 0; 
 
  Wire.begin(); 
  for (byte i = 8; i < 120; i++)  // Loop คนหา Address  
  { 
    Wire.beginTransmission (i); 
    if (Wire.endTransmission () == 0) 
      { 
      Serial.print ("Found address: "); 
      Serial.print (i, DEC); 
      Serial.print (" (0x"); 
      Serial.print (i, HEX); 
      Serial.println (")"); 
      count++; 
      delay (1);  
      }  
  }  
  Serial.println ("Done."); 
  Serial.print ("Found "); 
  Serial.print (count, DEC); 
  Serial.println (" device(s)."); 
}

void setup() {
  Wire.begin();
  Serial.begin(9600);

  Serial.println("Scanning for I2C device...");
  I2C_bus_scan();
}

void loop() {
  delay(5000);
  I2C_bus_scan();
}
