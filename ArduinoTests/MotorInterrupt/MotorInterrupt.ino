const int dirPin = 13;
const int stepPin = 12;
const int opAmpPin = 3;

const int rawPin = A0;
const int potPin = A1;

volatile bool spinMotorFlag = true;

String part1 = "Sens1: ";
String part2 = "   Pot1: ";
String part3 = "   Dig: ";

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  pinMode(opAmpPin, INPUT);

  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);

  attachInterrupt(digitalPinToInterrupt(opAmpPin), toggleMotor, RISING);

  Serial.begin(9600);
}

void loop() {
  //int rawInt = analogRead(rawPin);
  //int potInt = analogRead(potPin);
  //int digInt = digitalRead(opAmpPin);
  //String toPrint = part1 + rawInt + part2 + potInt + part3 + digInt;
  //Serial.println(toPrint);
  if (spinMotorFlag) {
    sendStep();
  }
  else{
    delay(500);
    moveMotor(200, false);
    Serial.println("Stopping!");
    delay(5000);
    spinMotorFlag = true;
  }
}

void sendStep(){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(300);
}

void moveMotor(int numSteps, bool dir){
  if (!dir){
    digitalWrite(dirPin, !digitalRead(dirPin));
  }
  
  for(int i = 1; i <= numSteps; i++){
    sendStep(); 
  }
  
  if (!dir){
    digitalWrite(dirPin, !digitalRead(dirPin));
  }
}

void toggleMotor(){
  digitalWrite(stepPin, LOW);
  spinMotorFlag = false;
}
