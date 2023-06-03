#include <Arduino.h>
#include <Stepper.h>
#include <ezButton.h>
#include <SoftwareSerial.h>

const byte rxPin = GPIOR13;
const byte txPin = GPIOR14;

int STEPS_PER_LETTER = 51;
int CURRENT_POSITION = 3000;
int ledState = LOW;
int TARGET_POSITION = 29 * STEPS_PER_LETTER;

#define STEPPER_PIN_1 GPIOR03
#define STEPPER_PIN_2 GPIOR04
#define STEPPER_PIN_3 GPIOR05
#define STEPPER_PIN_4 GPIOR06
#define LIMIT_SWITCH_PIN GPIOR07
#define NUMBER_OF_STEPS 2038

Stepper myStepper = Stepper(NUMBER_OF_STEPS, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4);
ezButton button(LIMIT_SWITCH_PIN);
SoftwareSerial mySerial (rxPin, txPin); 

void setup() {
  mySerial.begin(9600);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
  myStepper.setSpeed(15);
  button.setDebounceTime(50);
}

void loop() {
  if(mySerial.available())
  {
    String incomingMessage = mySerial.readString();
    int position = incomingMessage.substring(0, 2).toInt();
    if(position > -1 && position < 41){
      // Check if position is valid
      TARGET_POSITION = position * STEPS_PER_LETTER;
    }
    mySerial.print(incomingMessage.substring(2, sizeof(incomingMessage)));
  }
  button.loop();
  if(button.isPressed()){
    CURRENT_POSITION = 0;
    ledState = !ledState;
    digitalWrite(0, ledState);
  }

  if(CURRENT_POSITION != TARGET_POSITION){
    CURRENT_POSITION += 1;
    myStepper.step(1);
    delay(4);
    if(CURRENT_POSITION == TARGET_POSITION){  
      digitalWrite(STEPPER_PIN_1, LOW);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3, LOW);
      digitalWrite(STEPPER_PIN_4, LOW);
    }
  }
}