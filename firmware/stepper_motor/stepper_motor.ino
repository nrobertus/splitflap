//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
int stepsPerLetter = stepsPerRevolution / 40;

void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
}

void loop() {
  delay(5000);
  // Rotate CCW quickly at 10 RPM
  myStepper.setSpeed(5);
  myStepper.step(-15 * stepsPerLetter);
  delay(100000);
}

// 37.5 x 72.5 mm
