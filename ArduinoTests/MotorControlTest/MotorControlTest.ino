#include <Arduino.h>
#include "A4988.h"

#define MOTOR_STEPS 200
#define DIR 4
#define STEP 5
#define MS1 11
#define MS2 10
#define MS3 9

#define MICROSTEPS 1

A4988 stepper(MOTOR_STEPS, DIR, STEP);

void setup() {
  stepper.begin(10, MICROSTEPS);
}

void loop() {
  stepper.rotate(360);
  delay(1000);
}
