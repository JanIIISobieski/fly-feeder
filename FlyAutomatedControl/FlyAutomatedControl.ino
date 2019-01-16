#include <math.h>

//Enumerated list to label the cases easily
enum DeviceCases
{
  listen,
  align,
  fireFly,
  verify,
  suckFly,
  completion
};

int switchCase = listen; //first case, needs MATLAB input

// Needed for the rotation
int flyIndex = -1;
float expectedSteps = 1600.0; //200 steps / rot * 64 microstepping / 8 tubes
const int numTubes = 8;

char recievedChar = '\0';
char startSignal = 'b';
char flyPassedSignal = 'f';
char experimentalEndSignal = 'e';
char completionSignal = 'c';

char buf[2];


const int pcbPotPin = A0;
const int pcbRawPin = A1;
const int pcbAlignPin = 3;

const int stepPin = 12;
const int dirPin = 13;

volatile bool spinState = true;

// Functions for running the motor

void sendStep(int val1, int val2) {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(val1);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(val2);
}

float alignCartridge() {
  digitalWrite(dirPin, LOW);
  float steps = 0;
  while (spinState) {
    sendStep(10, 300);
    steps++;
  }

  spinState = true;
  return steps;
}

void getFromMATLAB() {
  if (Serial.available() > 0) {
    recievedChar = Serial.read();
  }
}



void setup() {
  pinMode(pcbPotPin, INPUT);
  pinMode(pcbRawPin, INPUT);
  pinMode(pcbAlignPin, INPUT);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(pcbAlignPin), stopSpin, FALLING);

  Serial.begin(9600);

  digitalWrite(dirPin, LOW);
}

void loop() {
  if(switchCase == listen) {
    getFromMATLAB();
    if (recievedChar == startSignal) {
      switchCase = align;
    }
  }

  else if (switchCase == align) {
    float numSteps = alignCartridge();
    flyIndex = (flyIndex + round(numSteps / expectedSteps)) % numTubes;
    
    if (numSteps < 100) {
      switchCase = align; //Too few steps, keep going
    }
    else {
      switchCase = fireFly;
    }
  }

  else if (switchCase == fireFly) {
    delay(1000);
    switchCase = verify;
  }

  else if (switchCase == verify) {
    delay(1000);
    switchCase = suckFly;
  }

  else if (switchCase == suckFly) {
    delay(1000);
    switchCase = listen;
  }

  else {
    delay(1000);
  }
}
