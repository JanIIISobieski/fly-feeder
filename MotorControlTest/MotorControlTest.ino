const int dirPin = 8;
const int stepPin = 7;

const int ledPin = 13;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  pinMode(ledPin, OUTPUT);

  for(int i = 0; i <= 5; i++){
    digitalWrite(ledPin, !digitalRead(ledPin));
    delay(500);
  }
  
  digitalWrite(dirPin, LOW);
}

void loop() {
  for(int i = 3000; i >= 300; i--){
    for(int k = 0; k <= 10; k++){
      sendStep(i);
    }
  }
  delay(1000);
  digitalWrite(dirPin, !digitalRead(dirPin));
}

void sendStep(int speedVal){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(speedVal);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(speedVal);
}
