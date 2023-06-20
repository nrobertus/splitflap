#include <Arduino.h>
#include <SoftwareSerial.h>

const byte rxPin = 22;
const byte txPin = 23;

const String messages [] = {
  "brb",
  "yes",
  "no!",
  " a "
};

int messageIndex = 0;

SoftwareSerial mySerial (rxPin, txPin); 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
      mySerial.println(messages[messageIndex]);
      messageIndex++;
      if(messageIndex > sizeof(messages) - 1){
        messageIndex = 0;
      }
      delay(5000);
}