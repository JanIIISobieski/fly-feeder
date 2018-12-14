const int relayPin1 = 5;

const int trimPot1 = A0;
const int trimPot2 = A1;

const int flyPin = A2;

const int stepPin = 13;
const int dirPin  = 12;

void setup() {
  pinMode(relayPin1, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(flyPin, INPUT);
  
  digitalWrite(relayPin1, LOW);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW);

  Serial.begin(9600);
}

void loop() {
  int flySensor = analogRead(flyPin);
  Serial.println(flySensor);
  delay(250);
}

void sendStep(int val1, int val2){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(550);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(450);
}
