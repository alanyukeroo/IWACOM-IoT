
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
int Index1,Index2,Index3,Index4,Index5;
String secondValue, thirdValue, fourthValue,fifthValue;

void sendSensor()
{
  String ph = secondValue;
  String d = thirdValue;
  String t = fourthValue;
  String kran = fifthValue;


  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, ph);
  Blynk.virtualWrite(V1, d);
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, kran);
  

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

    while(Serial.available()>0)
  {
    delay(10);
    c = Serial.read();
    myString +=c;
  }

  if(myString.length()>0)
  {
      Index1 = myString.indexOf('|');
      Index2 = myString.indexOf('|', Index1+1);
      Index3 = myString.indexOf('|', Index2+1);
      Index4 = myString.indexOf('|', Index3+1);
      Index5 = myString.indexOf('|', Index4+1);

      secondValue = myString.substring(Index1+1, Index2);
      thirdValue = myString.substring(Index2+1, Index3);
      fourthValue = myString.substring(Index3+1, Index4);
      fifthValue = myString.substring(Index4+1, Index5);
      
      Serial.println();
      Serial.print("data pH:");Serial.println(secondValue);
      Serial.print("data DO:");Serial.println(thirdValue);
      Serial.print("data Tu:");Serial.println(fourthValue);
      Serial.print("Status Kran:");Serial.println(fifthValue);
      myString="";
       delay(1000);
  }
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
}
