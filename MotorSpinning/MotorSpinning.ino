const int dirPin = 5;
const int stepPin = 4;

const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);

  digitalWrite(ledPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  sendStep(600);
}

void sendStep(int speedVal){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(speedVal);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(speedVal);
}
