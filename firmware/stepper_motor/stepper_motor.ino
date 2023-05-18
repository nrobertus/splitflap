//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2048;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
int stepsPerLetter = -51;

void setup() {
    myStepper.setSpeed(15);
}

void moveLetters(int letters) {
  myStepper.step(letters * stepsPerLetter);
}

void loop() {
  delay(5000);
  moveLetters(25);
  delay(500);
  moveLetters(13);
  delay(500);
  moveLetters(37);
  delay(5000);
  moveLetters(6);
}

/*
 * a
 * b
 * c
 * d
 * e
 * f
 * g
 * h
 * i
 * j
 * k
 * l
 * m
 * n
 * o
 * p
 * q
 * r
 * s
 * t
 * u
 * v
 * w
 * x
 * y
 * z
 * 1
 * 2
 * 3
 * 4
 * 5
 * 6
 * 7
 * 8
 * 9
 * 0
 * ?
 * !
 * .
 *  
 */
