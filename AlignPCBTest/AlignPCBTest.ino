const int pcbPotPin = A0;
const int pcbRawPin = A1;
const int pcbAlignPin = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(pcbPotPin, INPUT);
  pinMode(pcbRawPin, INPUT);
  pinMode(pcbAlignPin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t potVal = analogRead(pcbPotPin);
  uint16_t rawVal = analogRead(pcbRawPin);

  uint8_t digRead = digitalRead(pcbAlignPin);

  Serial.print(rawVal);
  Serial.print("    ");
  Serial.print(potVal);
  Serial.print("    ");
  Serial.print(digRead);
  Serial.println("");

  delay(100);
}
