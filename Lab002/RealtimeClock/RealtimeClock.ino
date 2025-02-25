#include <WiFi.h>
#include "time.h"

const char* ssid = "HORIZON-Donut";
const char* pass = "AllMyFriendsHavePassAway-NeedMySelfToSingThisSong";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7 * 3600;  // Thailand GMT+7
const int   daylightOffset_sec = 0;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  Serial.print("connecting to wifi ");
  while (WiFi.status() != WL_CONNECTED)
  {
	  Serial.print(".");
	  delay(500);
  }
  Serial.print(" Connected!!!");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.print("Getting time from NTP...");
  printLocalTime();
}

void loop() {
  delay(1000);
  printLocalTime();
}

void printLocalTime()
{
	struct tm timeinfo;
	if(!getLocalTime(&timeinfo))
	{
		Serial.print("Failed to obtain time");

		return;
	}
	Serial.println(&timeinfo, "Time: %Y-%m-%d %H:%M:%S");
}
