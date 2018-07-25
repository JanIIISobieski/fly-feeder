const int dirPin = 12;
const int stepPin = 11;

const int ledPin = 13;

const int ms1Pin = 2;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ms1Pin, OUTPUT);

  pinMode(ledPin, OUTPUT);

  for(int i = 0; i <= 5; i++){
    digitalWrite(ledPin, !digitalRead(ledPin));
    delay(500);
  }

  digitalWrite(ms1Pin, LOW);
  digitalWrite(dirPin, LOW);
}

void loop() {
    for(int k = 0; k <= 199; k++){
      sendStep(800);
    }
  delay(1000);
  digitalWrite(ms1Pin, !digitalRead(ms1Pin));
}

void sendStep(int speedVal){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(speedVal);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(speedVal);
}
