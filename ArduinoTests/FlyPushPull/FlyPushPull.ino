#include <math.h>

// Enumerated list to label the cases easily
enum DeviceCases
{
  listen,
  align,
  open2Fire,
  fireFly,
  close2Exp,
  verify,
  open2Suck,
  suckFly,
  close2Rot,
  completion
};

int switchCase = listen; //first case, needs MATLAB input

// Needed for the rotation
int flyIndex = -1;
float expectedSteps = 1600.0; //200 steps / rot * 64 microstepping / 8 tubes
const int numTubes = 8;

// Communications
char recievedChar = '\0';
char startSignal = 'b';
char flyPassedSignal = 'f';
char experimentalEndSignal = 'e';
char completionSignal = 'c';

char buf[2];

// Cartridge alignment
const int pcbPotPin = A0;
const int pcbRawPin = A1;
const int pcbAlignPin = 3;

// Stepper motor
const int stepPin = 12;
const int dirPin = 13;

volatile bool spinState = true; //

// Solenoid
const int pushSol = 9;
const int suckSol = 10;

// Linear actuator
const int linMotSet1 = 4;
const int linMotSet2 = 5;
const int linMotSet3 = 6;

const int linMotFdbck1 = A3;
const int linMotFdbck2 = A4;
const int linMotFdbck3 = A5;

// Functions for running the stepper motor
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

void stopSpin() {
  spinState = false;
}

// Communications
void getFromMATLAB() {
  if (Serial.available() > 0) {
    recievedChar = Serial.read();
  }
}

// Solenoids
void triggerAirPush(){
  digitalWrite(pushSol, !digitalRead(pushSol));
}

void triggerSucker(){
  digitalWrite(suckSol, !digitalRead(suckSol));
}

// Linear Actuator
void openGates(){
  analogWrite(linMotSet1, 77);
  analogWrite(linMotSet2, 77);  
  delay(4000);
}

void closeGates(){
  analogWrite(linMotSet1, 20);
  analogWrite(linMotSet2, 20);
  delay(4000);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(pushSol, OUTPUT);
  pinMode(suckSol, OUTPUT); 
  pinMode(linMotSet1, OUTPUT);
  pinMode(linMotSet2, OUTPUT);
  
  digitalWrite(pushSol, LOW);
  digitalWrite(suckSol, LOW);

   delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //openGates();
  //triggerAirPush();
  //delay(5000);
  //triggerAirPush();
  //closeGates();
  //delay(5000);
  openGates();
  triggerSucker();
  delay(5000);
  triggerSucker();
  closeGates();
  delay(5000);
}
