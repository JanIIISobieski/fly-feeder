char alignString = 'a';
char passingString = 'p';
char messageSuccess = 's';

int tubeNum = 1;

char recievedChar;

int val = 1;

void setup() {
   Serial.begin(9600);
   pinMode(9, OUTPUT);
   digitalWrite(9, HIGH);
   delay(2000);
   digitalWrite(9, LOW);
   delay(2000);
   digitalWrite(9, HIGH);
   delay(2000);
   digitalWrite(9, LOW);
}

void loop() {
  if (val == 1){
    sendToMATLAB(alignString);
    val = 2;
    digitalWrite(9, LOW);
  }
  else {
    getFromMATLAB();
    sendToMATLAB(recievedChar);
    if (recievedChar == messageSuccess){
      digitalWrite(9, HIGH);
      delay(1000);
      digitalWrite(9, LOW);
      delay(1000);
      }
  }
}

void getFromMATLAB(){
  if (Serial.available() > 0){
    recievedChar = Serial.read();
  }
}

void sendToMATLAB(char message){
  Serial.println(message);
}
