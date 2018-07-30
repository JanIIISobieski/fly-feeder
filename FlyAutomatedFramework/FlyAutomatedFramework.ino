/*
 Name:		FlyAutomatedFramework.ino
 Created:	7/30/2018 2:34:43 PM
 Author:	Gabriel J. Antoniak
*/

const int ms1Pin = 2;
const int ms2Pin = 3;

const int stepPin = 4;
const int dirPin = 5;

const int relayLogic1 = 6;
const int relayLogic2 = 7;

const int can_fr_top_IR = A0;
const int can_fr_bot_IR = A1;
const int can_bk_top_IR = A2;
const int can_bk_bot_IR = A3;

const int con_fr_top_IR = A4;
const int con_fr_bot_IR = A5;
const int con_bk_top_IR = A6;
const int con_bk_bot_IR = A7;

const int align_IR = A8;

const int circDegree = 360;
const int numFlyTubes = 6;

// the setup function runs once when you press reset or power the board
void setup() {

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}

void moveMotor(int speedVal){
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

void stepMotor(int steps, int speedVal, bool dir){
	chooseMotorDir(dir);
	for (size_t i = 0; i < steps; i++)
	{
		moveMotor(speedVal);
	}
}