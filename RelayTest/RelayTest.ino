const int relayPin = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relayPin, !digitalRead(relayPin));
  delay(2500);
}
