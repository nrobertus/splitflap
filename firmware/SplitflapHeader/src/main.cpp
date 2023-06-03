#include <Arduino.h>
#include <SoftwareSerial.h>

const byte rxPin = 22;
const byte txPin = 23;

SoftwareSerial mySerial (rxPin, txPin); 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
    delay(6000);
    int letter = random(40);
    String letterOut;
    if(letter < 10){
      letterOut = " " + String(letter);
    } else {
      letterOut = String(letter);
    }
    Serial.println(letterOut);
    mySerial.println(letterOut);
}