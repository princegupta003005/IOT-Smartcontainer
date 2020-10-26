#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include<Servo.h>

char auth[] = "YOUR AUTH CODEFROM BLYNK APP";
char ssid[] = "YOUR WIFI NAME";
char pass[] = "YOUR WIFI PASSWORD";

Servo myservo;
#define TRIGGERPIN  11
#define ECHOPIN     12
#define IR          10

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600
ESP8266 wifi(&Serial);

long distance,duration;

void setup()
{
  myservo.attach(9);
  Serial.begin(ESP8266_BAUD);
  delay(10);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(IR, INPUT);
  Blynk.begin(auth, wifi, ssid, pass);
}

void sendSensor()
{
  // start working...
digitalWrite(TRIGGERPIN, LOW);
delayMicroseconds(2);
// Sets the TRIGGERPIN on HIGH state for 10 micro seconds
digitalWrite(TRIGGERPIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGERPIN, LOW);
// Reads the ECHOPIN1, returns the sound wave travel time in microseconds
duration = pulseIn(ECHOPIN, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
Blynk.virtualWrite(V1, distance);
delay(500);

if(digitalRead(IR))
{
  Serial.println("enter");
  myservo.write(120);
}

else
{
  myservo.write(0);
}
}

void loop()
{
  sendSensor();
  Blynk.run();
}