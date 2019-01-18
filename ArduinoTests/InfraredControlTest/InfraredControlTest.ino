const int IR_read_pin = A0;

void setup(){
  pinMode(IR_read_pin, INPUT);
  Serial.begin(9600);
}

void loop(){
  int read_val = analogRead(IR_read_pin);
  Serial.println(read_val);
  delay(100);
}

