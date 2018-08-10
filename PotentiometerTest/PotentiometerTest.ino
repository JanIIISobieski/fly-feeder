const int potentPin = A1;
const int irPin = A0;
const int ledPin = 13;

void setup() {
  pinMode(potentPin, INPUT);
  pinMode(irPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  int irVal = analogRead(irPin);
  int compVal = analogRead(potentPin);
  Serial.print(irVal);
  Serial.print(" ");
  Serial.println(compVal);
  toggleLight(irVal, compVal);
  delay(250);
}

void toggleLight(int val1, int val2){
  if(val1 > val2){
    digitalWrite(ledPin, LOW);  
  }
  else{
    digitalWrite(ledPin, HIGH);
  }
}

