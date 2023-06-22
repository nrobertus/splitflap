//Includes the Arduino Stepper Library and Software Serial
#include <Stepper.h>
#include <SoftwareSerial.h>


String letters [] = {
  "3",
  "2",
  "1",
  "z",
  "y",
  "x",
  "w",
  "v",
  "u",
  "t",
  "s",
  "r",
  "q",
  "p",
  "o",
  "n",
  "m",
  "l",
  "k",
  "j",
  "i",
  "h",
  "g",
  "f",
  "e",
  "d",
  "c",
  "b",
  "a",
  " ",
  ".",
  "!",
  "?",
  "0",
  "9",
  "8",
  "7",
  "6",
  "5",
  "4",
};


#define INTERRUPT_PIN 2
#define SERIAL_RX 3
#define SERIAL_TX 4
#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11

// Constants
const String message = "h!";
const int STEPS_PER_REVOLUTION = 2038;
const int STEPS_PER_LETTER = 51;
const int STEPS_OFFSET = 0;

// Variables
int currentPosition = 3000;
int targetPosition = 3000;
String serialInput = "";

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(STEPS_PER_REVOLUTION, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4);
SoftwareSerial softSerial(SERIAL_RX, SERIAL_TX); // RX, TX


void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);
  myStepper.setSpeed(15);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), limit_switch_activated, CHANGE);
  pinMode(LED_BUILTIN, OUTPUT);
  // Do this so the first thing it tries is going to a home position
  goToLetter(" ");
}

void limit_switch_activated() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 1000ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 1000)
  {
    currentPosition = 0;
  }
  last_interrupt_time = interrupt_time;
}

void moveStepper(int steps) {
  currentPosition += steps;
  myStepper.step(steps);
}

void goToLetter(String letter) {
  Serial.println("GOING TO FIND: " + letter);
  bool found = false;
  for (int x = 0; x < sizeof(letters); x++) {
    if (letters[x] == letter) {
      found = true;
      targetPosition = (x * STEPS_PER_LETTER ) + STEPS_OFFSET;
    }
  }
  if (!found) {
    goToLetter(" ");
  }
}

bool isValidLetter(char letter) {
  bool isValid = false;
  for(int x = 0; x < sizeof(letters); x++) {
    if(letters[x] == String(letter)){
      isValid = true;
    }
  }
  return isValid;
}

void loop() {
  if (currentPosition != targetPosition) {
    moveStepper(1);
  } else {
    digitalWrite(STEPPER_PIN_1, LOW);
    digitalWrite(STEPPER_PIN_2, LOW);
    digitalWrite(STEPPER_PIN_3, LOW);
    digitalWrite(STEPPER_PIN_4, LOW);
  }
  if (softSerial.available() > 0)
  {
    char character = softSerial.read(); // Receive a single character from the software serial port
    if(isValidLetter(character)){
      serialInput.concat(character); // Add the received character to the receive buffer  
    }
    if (character == '\n' && serialInput.length() > 0)
    {
      String target = serialInput.substring(0, 1);
      String remainder = serialInput.substring(1, serialInput.length());
      Serial.println(target);
      Serial.println(remainder);
      Serial.println("=================");
      goToLetter(target);
      softSerial.println(remainder);
      serialInput = "";
    }
  }
}
