String myString;
char c;
int Index1,Index2,Index3,Index4,Index5,Index6;
String secondValue, thirdValue, fourthValue, fifthValue, firstValue;
void setup()
{              
   Serial.begin(9600);
}
void loop()
{
  while (Serial.available()>0)
  {
    delay(10);
    c = Serial.read();
    myString += c;
  }
    if (myString.length()>0)
    {
      Index1 = myString.indexOf('|');
      Index2 = myString.indexOf('|', Index1+1);
      Index3 = myString.indexOf('|', Index2+1);
      Index4 = myString.indexOf('|', Index3+1);
      Index5 = myString.indexOf('|', Index4+1);
      Index6 = myString.indexOf('|', Index5+1);
      secondValue = myString.substring(Index1+1, Index2);
      thirdValue = myString.substring(Index2+1, Index3);
      fourthValue = myString.substring(Index3+1, Index4);
      fifthValue = myString.substring(Index4+1, Index5);
      firstValue = myString.substring(Index5+1, Index6);
//Serial.println(Index1);
      Serial.print("data 1:");Serial.println(secondValue);
      Serial.print("data 2:");Serial.println(thirdValue);
      Serial.print("data 3:");Serial.println(fourthValue);
      Serial.print("data 4:");Serial.println(fifthValue);
      Serial.print("data 5:");Serial.println(firstValue);
      myString="";
      }
     
}
