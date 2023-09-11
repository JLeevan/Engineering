/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <Arduino.h>
#include <WiFi.h>

const char* ssid     = "WIFI_SSID"; // Set your own SSID
const char* password = "WIFI_PASSWORD"; // Set your own WiFi password

void setClock() {
  configTime(0, 3600, "pool.ntp.org", "time.nist.gov");

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 10) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  printTime();
}

void printTime() {
  time_t nowSecs = time(nullptr);
  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time (GMT): "));
  Serial.print(asctime(&timeinfo));
  localtime_r(&nowSecs, &timeinfo); 
  Serial.print(F("Current time (Local): "));
  Serial.print(asctime(&timeinfo));
}


void setup()
{
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    setClock();
}

int value = 0;

void loop()
{
    delay(5000);
    printTime();

}
