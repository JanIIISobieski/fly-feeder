const int pcbPotPin = A0;
const int pcbRawPin = A1;
const int pcbAlignPin = 3;

const int stepPin = 12;
const int dirPin = 13;

volatile bool spinState = true;

void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:

  while(spinState){
    sendStep(10, 300);
  }

  delay(2500);
  spinState = true;
}

void stopSpin(){
  spinState = false;
}

void sendStep(int val1, int val2){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(val1);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(val2);
}
