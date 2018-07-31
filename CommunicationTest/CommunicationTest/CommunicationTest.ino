void setup() {
  Serial.begin(9600);
}

void loop() {
  int randVal = random(0, 10);
  Serial.println(randVal);
  delay(1000);
}
