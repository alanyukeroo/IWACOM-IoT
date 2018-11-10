#include <Servo.h> 
Servo servo1; 
int pos1 = 0; 
static float kekeruhan; 
static float teg; 

void setup() { 
Serial.begin(9600); //Baud rate: 9600 
servo1.attach(9); 
servo1.write(170); 
} 
void loop() { 
int val = analogRead(A0); 
teg = val*(5.0/1024); 
kekeruhan = 100.00 - (teg/4.16)*100.00; 
Serial.print(teg); 
Serial.print(" "); 
Serial.print("Nilai ADC = "); 
Serial.print(val); 
Serial.print(" "); 
Serial.print("Nilai kekeruhan = "); 
Serial.print(kekeruhan); 
Serial.println(" NTU"); 
delay(1000); 
if(kekeruhan >=60){ 
/*for(pos1 = 100; pos1 >= 1; pos1-=1){ 
servo1.write(pos1); 
delay(10); 
}*/ 
servo1.write(75); 
}else{ 
/*for(pos1 = 0; pos1 < 100; pos1+=1){ 
servo1.write(pos1); 
delay(10); 
}*/ 
servo1.write(170); 
} 
}
