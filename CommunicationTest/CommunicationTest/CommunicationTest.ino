String align_string = "Cartridge aligned";
String fly_string = "Fly pased through";

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(align_string);
  delay(1000);
  Serial.println(fly_string);
  delay(1000);
}
