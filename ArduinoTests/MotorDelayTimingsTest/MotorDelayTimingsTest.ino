const int relayPin1 = 5;

const int trimPot1 = A0;
const int trimPot2 = A1;

const int stepPin = 11;
const int dirPin  = 12;


void setup() {
  pinMode(relayPin1, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  digitalWrite(relayPin1, LOW);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, HIGH);

  pinMode(trimPot1, INPUT);
  pinMode(trimPot2, INPUT);

  Serial.begin(9600);
}

void loop() {
  int t1Val = analogRead(trimPot1);
  int t2Val = analogRead(trimPot2);

  sendStep(t1Val, t2Val);

  Serial.print(t1Val);
  Serial.print("  ");
  Serial.println(t2Val);
}

void sendStep(int val1, int val2){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(val1);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(val2);  
}
