const int dirPin = 7;
const int stepPin = 6;
const int opAmpPin = 3;
const int ledPin = 13;

volatile bool spinMotorFlag = true;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(opAmpPin, INPUT);

  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);

  digitalWrite(ledPin, HIGH);
  
  attachInterrupt(digitalPinToInterrupt(opAmpPin), toggleMotor, RISING);
}

void loop() {
  if (spinMotorFlag) {
    sendStep(600);
  }
  else{
    delay(5000);
    spinMotorFlag = true;
    digitalWrite(ledPin, HIGH);
  }
}

void sendStep(int speedVal){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(speedVal);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(speedVal);
}

void toggleMotor(){
  digitalWrite(stepPin, LOW);
  digitalWrite(ledPin, LOW);
  spinMotorFlag = false;
}
