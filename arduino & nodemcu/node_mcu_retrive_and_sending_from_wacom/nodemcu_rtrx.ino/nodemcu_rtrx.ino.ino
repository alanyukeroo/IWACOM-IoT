#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
SimpleTimer timer;
String sensorData;


BLYNK_READ(V0) //Blynk app has something on V5
{
  sensorData = Serial.readString(); //reading the sensor on A0
  Blynk.virtualWrite(V0, sensorData); //sending to Blynk
}



char auth[] = "0234093d03824eafbcf08a6770d82456";  
char ssid[] = "OPPO A37f";
char pass[] = "12345678";
bool Connected2Blynk = false;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
//  while(WiFi.status() != WL_CONNECTED){
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi Connected");
//  Serial.println("IP Address : ");
//  Serial.println(WiFi.localIP());
//
//  Blynk.config(auth);
//  Blynk.connect(3333);
  while(Blynk.connect() == false){
    
  }
//  Serial.println("Terkoneksi Blynk!");
//  timer.setInterval(11000L, CheckConnection); 
//  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
//  }
  timer.setInterval(1000L, myTimerEvent);
}

void myTimerEvent(){
  sensorData = Serial.readString();
  Blynk.virtualWrite(V0, sensorData);
}

void CheckConnection(){
  Connected2Blynk = Blynk.connected();
  if(!Connected2Blynk){
    Serial.println("Not connected to Blynk server"); 
    Blynk.connect(3333);  // timeout set to 10 seconds and then continue without Blynk  
  }
  else{
    Serial.println("Connected to Blynk server");     
  }
}

void loop() { // run over and over
  if (Serial.available()) {
    Serial.write(Serial.read());
    if(Connected2Blynk){
    Blynk.run();
  }
  timer.run();
  }
}
