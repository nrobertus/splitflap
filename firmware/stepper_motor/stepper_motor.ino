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

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
const byte interruptPin = 2;
int stepsPerLetter = 51;
bool CLICKED = false;
int currentPosition = 0;

void setup() {
  myStepper.setSpeed(10);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void homeStepper(){
  moveStepper(stepsPerRevolution * 1.5);
}

void moveStepper(int steps) {
  currentPosition += steps;
  myStepper.step(steps);
}

void findPosition(int steps) {
  while (currentPosition != steps) {
    moveStepper(1);
  }
}

void goToLetter(String letter){
  for(int x = 0; x < sizeof(letters); x++){
    if(letters[x] == letter){
      findPosition(x * stepsPerLetter);
    }
  }
}

void loop() {
  if(!CLICKED){
    homeStepper();
  }
  delay(5000);
  goToLetter("i");
  delay(1000);
  goToLetter("n");
  delay(1000);
  goToLetter("t");
  delay(1000);
  goToLetter("e");
  delay(1000);
  goToLetter("r");
  delay(1000);
  goToLetter("l");
  delay(1000);
  goToLetter("o");
  delay(1000);
  goToLetter("p");
  delay(1000);
  goToLetter("e");
  delay(1000);
  goToLetter("r");
  delay(1000);
  goToLetter(" ");
  delay(1000);
  goToLetter("c");
  delay(1000);
  goToLetter("r");
  delay(1000);
  goToLetter("e");
  delay(1000);
  goToLetter("a");
  delay(1000);
  goToLetter("t");
  delay(1000);
  goToLetter("i");
  delay(1000);
  goToLetter("v");
  delay(1000);
  goToLetter("e");
  delay(1000);
  goToLetter(" ");
  delay(1000);
  goToLetter("b");
  delay(1000);
  goToLetter("r");
  delay(1000);
  goToLetter("e");
  delay(1000);
  goToLetter("h");
  delay(1000);
  goToLetter("!");
  delay(1000);
}

void blink() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 1000)
  {
    CLICKED = true;
    currentPosition = 0;
  }
  last_interrupt_time = interrupt_time;
}

/*
   3
   4
   5
   6
   7
   8
   9
   0
   ?
   !
   .

   a
   b
   c
   d
   e
   f
   g
   h
   i
   j
   k
   l
   m
   n
   o
   p
   q
   r
   s
   t
   u
   v
   w
   x
   y
   z
   1
   2
*/
