#include <Arduino.h>
#include <SoftwareSerial.h>

const byte rxPin = 22;
const byte txPin = 23;

const String message = "testing";

SoftwareSerial mySerial (rxPin, txPin); 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
      mySerial.println(message);
      delay(8000);
}