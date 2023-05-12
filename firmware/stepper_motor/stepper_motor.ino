//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2048;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
int stepsPerLetter = -53;

void setup() {
    myStepper.setSpeed(10);
}

void moveLetters(int letters) {
  myStepper.step(letters * stepsPerLetter);
}

void loop() {
  delay(500);
  // Rotate CCW quickly at 10 RPM
  moveLetters(1);
}
