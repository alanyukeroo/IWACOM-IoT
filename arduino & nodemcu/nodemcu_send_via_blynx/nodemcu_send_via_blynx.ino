
//SoftwareSerial DebugSerial(2, 3); // RX, TX



#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
SimpleTimer timer;

char auth[] = "0234093d03824eafbcf08a6770d82456";  
char ssid[] = "OPPO A37f";
char pass[] = "12345678";
String myString;
char c;
int Index1,Index2,Index3,Index4;
String secondValue, thirdValue, fourthValue;

void sendSensor()
{
  float ph = 1;
  float d = 2;
  float t = 3;


  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, ph);
  Blynk.virtualWrite(V1, d);
  Blynk.virtualWrite(V2, t);
  

}

void setup()
{
  Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);
    // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
}
