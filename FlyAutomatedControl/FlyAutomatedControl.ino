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
float expectedSteps = 1600.0; //200 steps per rotation * 64 microstepping / 8 tubes
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

void moveMotor(int numSteps, bool dir){
  if (!dir){
    digitalWrite(dirPin, !digitalRead(dirPin));
  }
  
  for(int i = 1; i <= numSteps; i++){
    sendStep(10, 300); 
  }
  
  if (!dir){
    digitalWrite(dirPin, !digitalRead(dirPin));
  }
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
  analogWrite(linMotSet1, 245);
  analogWrite(linMotSet2, 245);  
}

void closeGates(){
  analogWrite(linMotSet1, 5);
  analogWrite(linMotSet2, 5);
}

void setup() {
  pinMode(pcbPotPin, INPUT);
  pinMode(pcbRawPin, INPUT);
  pinMode(pcbAlignPin, INPUT);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(linMotSet1, OUTPUT);
  pinMode(linMotSet2, OUTPUT);

  pinMode(linMotFdbck1, INPUT);
  pinMode(linMotFdbck2, INPUT);

  pinMode(pushSol, OUTPUT);
  pinMode(suckSol, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(pcbAlignPin), stopSpin, FALLING);

  digitalWrite(dirPin, LOW);
  digitalWrite(pushSol, LOW);
  digitalWrite(suckSol, LOW);
  analogWrite(linMotSet1, 0);
  analogWrite(linMotSet2, 0);

  Serial.begin(9600);
}

void loop() {
  if (switchCase == listen) {
    getFromMATLAB();
    if (recievedChar == startSignal) {
      switchCase = align;
      recievedChar = '\0';
    }
   if (recievedChar == completionSignal){
      switchCase = completion;
   }
  }

  else if (switchCase == align) {
    float numSteps = alignCartridge();
    flyIndex = (flyIndex + round(numSteps / expectedSteps)) % numTubes;
    
    if (numSteps < 400) {
      switchCase = align; //Too few steps, keep going
    }
    else {
      delay(500);
      moveMotor(300, false); //move motor back to correct position
      Serial.println(itoa(flyIndex, buf, 10)); //integer to ascii character (itoa) needed for proper sending
      switchCase = open2Fire;
    }
  }

  else if (switchCase == open2Fire){
    openGates();
    delay(1000);
    triggerAirPush();
    delay(3000);
    switchCase = fireFly;
  }
  
  else if (switchCase == fireFly) {
    int flyPass = random(1, 100);
    bool matlabFirst = false;

    delay(25);
    
    getFromMATLAB();
    
    if (recievedChar == flyPassedSignal) {
      recievedChar = '\0';
      matlabFirst = true;
      switchCase = close2Exp;
    }
    
    if (!matlabFirst && flyPass>96) {
      Serial.println(flyPassedSignal);
      switchCase = close2Exp;
    }
  }

  else if (switchCase == close2Exp){
    triggerAirPush();
    closeGates();
    switchCase = verify;
    delay(5000);
  }
  
  else if (switchCase == verify) {
    delay(10000);
    switchCase = open2Suck;
  }

  else if (switchCase == open2Suck){
    openGates();
    delay(1000);
    triggerSucker();
    switchCase = suckFly;
  }
  
  else if (switchCase == suckFly) {
    delay(5000);
    switchCase = close2Rot;
  }

  else if (switchCase == close2Rot){
    closeGates();
    triggerSucker();
    delay(5000);
    switchCase = listen;  
  }

  else if (switchCase == completion) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(1000);
  }

  else {
    delay(1000);
  }
}
