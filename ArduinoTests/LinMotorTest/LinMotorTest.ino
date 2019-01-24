const int linMotorFeedback = A3;
const int linMotorSetter = 4;

void setup() {
  pinMode(linMotorFeedback, INPUT);
  pinMode(linMotorSetter, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int setting = random(5, 245);
  analogWrite(linMotorSetter, setting);
  int readValue = analogRead(linMotorFeedback);
  Serial.print(setting);
  Serial.print("   ");
  Serial.println(readValue);
  delay(4000);
}
