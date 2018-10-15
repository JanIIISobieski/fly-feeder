/*
 Name:		FlyAutomatedFramework.ino
 Created:	7/30/2018 2:34:43 PM
 Author:	Gabriel Antoniak
*/

//MS pins on motor driver stepper
const int ms1 = 9;	//doubles stepping (1 -> 2, or 4 -> 8)
const int ms2 = 10;	//quadruples stepping (1 -> 4, 2-> 8)
const int ms3 = 11;	//doubles stepping (only from 8 -> 16)

const int stepPin = 5;	//send pulse to move motor
const int dirPin = 4;	//set to high or low to change direction

const int relayLogic1 = 6;	//activate relay 1
const int relayLogic2 = 7;	//activate relay 2

const int align_IR = A0;
const int fly_IR = A1;

const int align_digital = 2;
const int fly_digital = 3;
volatile int spin_motor = 1;

int motor1BaseSteps = 400;
int numFlyTubes = 8;

int stepsPerRot;
int stepsToNextFly;

char aligned[] = "Cartridge aligned";
char fly_passed[] = "Fly passed";

void setup() {
	Serial.begin(9600);

	//pinMode(ms1, OUTPUT);
	//pinMode(ms2, OUTPUT);
	//pinMode(ms3, OUTPUT);

	//digitalWrite(ms1, LOW);
	//digitalWrite(ms2, LOW);
	//digitalWrite(ms3, LOW);

	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);

	digitalWrite(stepPin, LOW);
	digitalWrite(dirPin, LOW);

	pinMode(relayLogic1, OUTPUT);
	pinMode(relayLogic2, OUTPUT);

	//stepsPerRot = findStepsPerRot(motor1BaseSteps);
	stepsPerRot = 400;
	stepsToNextFly = findStepsToNextFly(stepsPerRot, numFlyTubes);

	attachInterrupt(digitalPinToInterrupt(align_digital), changeSpinState, FALLING);

	delay(5000);

	int steps_needed = alignMotorWithIR();
	Serial.println(steps_needed);
}

void loop() {
	digitalWrite(LED_BUILTIN, !digitalRead(!LED_BUILTIN));
	delay(500);
}

int findStepsToNextFly(int stepsPerRot, int numFlyTubes){
	float circRot = 360.0;
	int stepsToFly = floor((circRot / ((float) numFlyTubes)) * ((float) stepsPerRot));
	return stepsToFly;
}

int findStepsPerRot(int baseSteps){
	if (digitalRead(ms1) == HIGH)
	{
		baseSteps = baseSteps * 2;
	}

	if (digitalRead(ms2) == HIGH){
		baseSteps = baseSteps * 4;
	}

	if (digitalRead(ms3) == HIGH){
		baseSteps = baseSteps * 2;
	}

	return baseSteps;
}

void stepMotor(int speedVal){
	digitalWrite(stepPin, HIGH);
	delayMicroseconds(speedVal);
	digitalWrite(stepPin, LOW);
	delayMicroseconds(speedVal);
}

void chooseMotorDir(bool dir){
	if (dir) {
		digitalWrite(dirPin, HIGH);
	}
	else {
		digitalWrite(dirPin, LOW);
	}
}

void moveMotor(int steps, int speedVal, bool dir){
	chooseMotorDir(dir);
	for (int i = 0; i < steps; i++)
	{
		stepMotor(speedVal);
	}
}

void fireFly(){

}

int alignMotorWithIR() {
	int steps = 0;
	while (spin_motor == 1)
	{
		moveMotor(1, 600, true);
		int val = analogRead(align_IR);
		steps++;
		delay(250);
	}
	digitalWrite(stepPin, LOW);
	sendToMATLAB(aligned);
	return steps;
}

void changeSpinState() {
	spin_motor = 0;
}

void sendToMATLAB(String code){
	Serial.println(code);
}

String readFromMATLAB(){
	String read = Serial.readString();
	return read;
}