const int potent_pin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(potent_pin, INPUT);
}

void loop() {
  int read_val = analogRead(potent_pin);
  Serial.println(read_val);
  delay(200);
}
