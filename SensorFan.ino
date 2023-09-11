/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  NOTE: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_TEMPLATE_ID "TMPLLBmqiRA7"
#define BLYNK_TEMPLATE_NAME "Fan Control Template"
#define BLYNK_AUTH_TOKEN "0h0jKxfKmj4LOA4JwcZ1JxLxV-maWYbG"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "BT-Q8C2H9";
char pass[] = "PbRLEkAmHn4yRa";
BlynkTimer timer;
int virtualPin = 12;//the pin to read for blynk inputs

int fPin = 14;int fState = 0;
int sPin = 32;int sState = 0;

BLYNK_WRITE(V12)
{
  // Set incoming value from pin V12 to a variable
  int value = param.asInt();
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(virtualPin, HIGH);
  // Update state
  Blynk.virtualWrite(V12, value);
}


// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}
void Entered(){
  Blynk.logEvent("entered", "Someone Walked in");
}
void setup()
{
  pinMode(fPin, INPUT);pinMode(sPin, INPUT);
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  pinMode(virtualPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  Blynk.run();
  timer.run();
  delay(1000);
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!

  fState = digitalRead(fPin);
  sState = digitalRead(sPin);
  delay(1000);
  if (fState == HIGH){
    Serial.println("MOTION DETECTED ON FIRST SENSOR");
    delay(1000);
    if(sState == HIGH){
      Serial.println("SUBJECT IS IN!");
      delay(1000);
      Blynk.logEvent("entered", "Someone Walked in");
    }else{
      Serial.println("Subject didn't go in ");
      delay(1000);
    }
  }

  else if (sState == HIGH){
    delay(1000);
    Serial.println("DETECTED MOTION ON SECOND SENSOR");
    delay(1000);
    if(fState == HIGH){
      Serial.println("SUBJECT HAS LEFT!");
      Blynk.logEvent("exited", "Someone Left");
      delay(1000);
    }else{
      Serial.println("Subject didn't leave");
      delay(1000);
    }
  }

  else{
    Serial.println("No motion detected");
    delay(1000);
  }
}



