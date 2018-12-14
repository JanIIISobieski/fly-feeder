const int dirPin    = 12;
const int stepPin   = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  digitalWrite(stepPin, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 64*200; i++) {
    sendStep(10, 300);
  }

  delay(2000);
  digitalWrite(dirPin, !digitalRead(dirPin));
}

void sendStep(int val1, int val2){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(val1);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(val2);
}
