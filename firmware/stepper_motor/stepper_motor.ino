//Includes the Arduino Stepper Library
#include <Stepper.h>

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

// Constants
const int stepsPerRevolution = 2038;
const int stepsPerLetter = 51;
const byte interruptPin = 7;
const String message = "somebody once told me the world is gonna roll me. i aint the sharpest tool in the shed. she was looking kinda dumb with her finger and her thumb in the shape of an l on her forehead.";


// Variables
bool IS_CALIBRATED = false;
int currentPosition = 3000;
bool LED_IS_ON = false;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 18, 20, 19, 21);


void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(15);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), limit_switch_activated, CHANGE);
  pinMode(LED_BUILTIN, OUTPUT);
}

void limit_switch_activated() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 1000ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 1000)
  {
    Serial.println("INTERRUPT");
    IS_CALIBRATED = true;
    currentPosition = 0;
    if (LED_IS_ON) {
      digitalWrite(LED_BUILTIN, LOW);
      LED_IS_ON = false;
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
      LED_IS_ON = true;
    }
  }
  last_interrupt_time = interrupt_time;
}

void homeStepper() {
  goToLetter(" ");
}

void moveStepper(int steps) {
  currentPosition += steps;
  myStepper.step(steps);
}

void findPosition(int steps) {
  while (currentPosition != steps) {
    moveStepper(1);
  }
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(20, LOW);
  digitalWrite(21, LOW);
}

void goToLetter(String letter) {
  for (int x = 0; x < sizeof(letters); x++) {
    if (letters[x] == letter) {
      findPosition(x * stepsPerLetter);
    }
  }
}

void loop() {
  if (!IS_CALIBRATED) {
    homeStepper();
  }
  for (auto c : message) {
    goToLetter(String(c));
    delay(1000);
  };
  delay(4000);
}
