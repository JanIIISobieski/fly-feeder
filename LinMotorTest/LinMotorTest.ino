const int linMotorFeedback = A3;
const int linMotorSetter = 4;

void setup() {
  pinMode(linMotorFeedback, INPUT);
  pinMode(linMotorSetter, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int setting = random(0, 255);
  analogWrite(linMotorSetter, setting);
  int readValue = analogRead(linMotorFeedback);
  Serial.print(setting);
  Serial.print("   ");
  Serial.println(readValue);
  delay(4000);
}
