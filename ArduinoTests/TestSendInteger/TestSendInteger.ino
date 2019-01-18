int value = 0;
char buf[2];

void setup() {
  Serial.begin(9600);
}

void loop() {
  value++;
  int toSend = value % 8;
  //Serial.print(toSend);
  //Serial.print("   ");
  Serial.println(itoa(toSend, buf, 10)); //integer to send, buffer size (representation + escape character), base to use
  delay(250);
}
