#include <WiFi.h>
#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7 * 3600;  // Thailand GMT+7
const int   daylightOffset_sec = 0;

void setup() {
  Serial.begin(115200);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    Serial.println(&timeinfo, "%Y-%m-%d %H:%M:%S");
  }
  delay(1000);
}
