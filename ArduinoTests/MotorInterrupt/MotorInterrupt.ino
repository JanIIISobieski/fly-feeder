const int dirPin = 13;
const int stepPin = 12;
const int opAmpPin = 3;;

volatile bool spinMotorFlag = true;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  pinMode(opAmpPin, INPUT);

  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);

  attachInterrupt(digitalPinToInterrupt(opAmpPin), toggleMotor, RISING);
}

void loop() {
  if (spinMotorFlag) {
    sendStep(1000);
  }
  else{
    delay(5000);
    spinMotorFlag = true;
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
  spinMotorFlag = false;
}
