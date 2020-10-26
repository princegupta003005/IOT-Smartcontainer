#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3); //connect esp rx pin to 3
                               //connect esp tx pin to 2

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }

  mySerial.begin(115200);
 
  mySerial.println("AT");
  delay(1000);
  mySerial.println("AT+CWMODE=1");
  delay(1000);
  mySerial.println("AT+UART_DEF=9600,8,1,0,0");

}

void loop()
{
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  if (Serial.available())
  {
    mySerial.write(Serial.read());
  }
}