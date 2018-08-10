const int ledPin = 13;
const int opAmpPin = 3;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
  digitalWrite(ledPin, HIGH);
  attachInterrupt(digitalPinToInterrupt(opAmpPin), toggleLight, RISING);
}

void loop() {

}

void toggleLight(){
  digitalWrite(ledPin, LOW);
}

