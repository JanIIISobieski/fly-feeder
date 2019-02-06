const int linMotorFeedback = A3;
const int linMotorSetter = 4;

int setting;

void setup() {
  pinMode(linMotorFeedback, INPUT);
  pinMode(linMotorSetter, OUTPUT);

  Serial.begin(9600);

  setting = 77;
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(linMotorSetter, setting);
  int readValue = analogRead(linMotorFeedback);
  Serial.print(setting);
  Serial.print("   ");
  Serial.println(readValue);
  delay(5000);
  if (setting == 77){
    setting = 20;
  }
  else {
    setting = 77;  
  }
}
