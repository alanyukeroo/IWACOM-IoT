#include <Ethernet.h>
#include <SPI.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 115);
EthernetClient client;
const int trigPin = 2;
const int echoPin = 3;

String data;

int readingInterval = 5; // in minutes

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac, ip); 

  data = "";
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, inc, cm;

  // Sending data pulse through trigPin
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  // Start receiving signal
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert into inches and cm
  inc = toInc(duration);
  cm = toCm(duration);

  data = "inc=" + String(inc) + "&cm=" + String(cm);

  if(client.connect("192.168.1.1", 1007)) { // REPLACE WITH SERVER ADDRESS
    client.println("POST /php_app/includes/add.php HTTP/1.1");
    client.println("Host: 192.168.1.1"); // SERVER ADDRESS TOO
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
  } 

  if (client.connected()) {
    client.stop(); // DISCONNECT FROM THE SERVER
  }

  Serial.print(cm);
  Serial.println("Cm");
  
  delay(40000); // WAIT FIVE MINUTES BEFORE SENDING AGAIN
}

long toInc(long microseconds)
{
  return microseconds /74 /2;
}

long toCm(long microseconds)
{
  return microseconds /29 /2;
}
