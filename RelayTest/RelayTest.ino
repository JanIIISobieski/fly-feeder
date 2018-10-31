const int relayPin = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  digitalWrite(relayPin, !digitalRead(relayPin));
  delay(1000);
  digitalWrite(relayPin, !digitalRead(relayPin));
}
