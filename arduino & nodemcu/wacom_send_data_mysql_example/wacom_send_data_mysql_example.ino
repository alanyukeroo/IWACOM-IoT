//#include <DHT.h>/
#include <Ethernet.h>
#include <SPI.h>
#include <Servo.h> 
Servo servo1; 
int pos1 = 0; 
static float kekeruhan; 
static float teg;
String kran;

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
IPAddress ip(192, 168, 1, 2);
EthernetClient client;

#define DHTPIN 2 // SENSOR PIN
#define DHTTYPE DHT11 // SENSOR TYPE - THE ADAFRUIT LIBRARY OFFERS SUPPORT FOR MORE MODELS
//DHT dht(DHTPIN, DHTTYPE);/

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250000; // READING INTERVAL


String data,data_serial;

void setup() { 
  servo1.attach(9); 
servo1.write(170); 
	Serial.begin(9600);
 
   Ethernet.begin(mac, ip);

//	if (Ethernet.begin(mac) == 0) {
//		Serial.println("Failed to configure Ethernet using DHCP"); 
//	}

//	dht.begin(); /
	delay(1000); // GIVE THE SENSOR SOME TIME TO START

//	h = (int) dht.readHumidity(); 
//	t = (int) dht.readTemperature(); 

	data = "";
  data_serial = "";
}

void loop(){
int val = analogRead(A0); 
teg = val*(5.0/1024); 
kekeruhan = 100.00 - (teg/4.16)*100.00; 
//Serial.print(teg); 
//Serial.print(" "); 
//Serial.print("Nilai ADC = "); 
//Serial.print(val); 
//Serial.print(" "); 
//Serial.print("Nilai kekeruhan = "); 
//Serial.print(kekeruhan); 
//Serial.println(" NTU"); 
delay(1000); 
if(kekeruhan >=60){ 
servo1.write(75); 
kran = "AKSES AIR DITUTUP";
}else{ 
servo1.write(170); 
kran = "AKSES AIR DIBUKA";
}

	currentMillis = millis();
	if(currentMillis - previousMillis > interval) { // READ ONLY ONCE PER INTERVAL
		previousMillis = currentMillis;
	//	h = (int) dht.readHumidity();
	//  t = (int) dht.readTemperature();

    
    }

	//data = "temp1=" + t + "&hum1=" + h;
//  data = "turbidity=1&ph=2&do=3";
//  data = "turbidity=" + t;/
//    data = "turbidity=" + t;
//    data += "&ph=" + ph;
//    data += "&do=" + d;

  float t = kekeruhan;
  float ph = random(5,8);
  float d = random(3,10);

    data = "turbidity=";
    data += kekeruhan;
    data += "&ph=";
    data += ph;
    data += "&do=";
    data += d;
    
    data_serial = "|";
    data_serial += t;
    data_serial += "|";
    data_serial += ph;
    data_serial += "|";
    data_serial += d;
    data_serial += "|";
    data_serial += kran;
    data_serial += "|";
	if (client.connect("192.168.1.1",80)) { // REPLACE WITH YOUR SERVER ADDRESS
    Serial.println(data_serial);
		client.println("POST /arduino/add.php HTTP/1.1"); 
		client.println("Host: 192.168.1.1"); // SERVER ADDRESS HERE TOO
		client.println("Content-Type: application/x-www-form-urlencoded"); 
		client.print("Content-Length: "); 
		client.println(data.length()); 
		client.println(); 
		client.print(data); 
	} 
 

	if (client.connected()) { 
		client.stop();	// DISCONNECT FROM THE SERVER
	}


	delay(1000); // WAIT FIVE MINUTES BEFORE SENDING AGAIN
}
