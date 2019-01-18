int flyIndex = 0;
float expectedSteps = 1600.0;
const int numTubes = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int randI = random(1400, 1700);
  flyIndex = (flyIndex + round(randI / expectedSteps)) % numTubes;
  Serial.print(randI);
  Serial.print("  ");
  Serial.println(flyIndex);
  delay(500);
}
