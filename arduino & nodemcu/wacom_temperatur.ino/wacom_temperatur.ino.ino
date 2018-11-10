//#include <DHT.h>/
#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
IPAddress ip(192, 168, 1, 2);
EthernetClient client;

#define DHTPIN 2 // SENSOR PIN
#define DHTTYPE DHT11 // SENSOR TYPE - THE ADAFRUIT LIBRARY OFFERS SUPPORT FOR MORE MODELS
//DHT dht(DHTPIN, DHTTYPE);/

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250000; // READING INTERVAL

int t = 1;	// TEMPERATURE VAR
int h = 2;	// HUMIDITY VAR
String data;

void setup() { 
	Serial.begin(9600);
  
   Ethernet.begin(mac, ip);

//	if (Ethernet.begin(mac) == 0) {
//		Serial.println("Failed to configure Ethernet using DHCP"); 
//	}

//	dht.begin(); /
	delay(10000); // GIVE THE SENSOR SOME TIME TO START

//	h = (int) dht.readHumidity(); 
//	t = (int) dht.readTemperature(); 

	data = "";
}

void loop(){

	currentMillis = millis();
	if(currentMillis - previousMillis > interval) { // READ ONLY ONCE PER INTERVAL
		previousMillis = currentMillis;
	//	h = (int) dht.readHumidity();
	//  t = (int) dht.readTemperature();
  h = 1;
  t = 2;
	}

	//data = "temp1=" + t + "&hum1=" + h;
  data = "temp1=1&hum1=2";

	if (client.connect("192.168.1.1",80)) { // REPLACE WITH YOUR SERVER ADDRESS
    Serial.println("Berhasil "+data);
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

	delay(2000); // WAIT FIVE MINUTES BEFORE SENDING AGAIN
}
