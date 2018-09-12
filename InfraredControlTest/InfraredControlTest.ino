const int IR_read_pin = A0;

void setup(){
  pinMode(IR_read_pin, INPUT);
}

void loop(){
  int read_val = analogRead(IR_read_pin);
  delay(100);
}

