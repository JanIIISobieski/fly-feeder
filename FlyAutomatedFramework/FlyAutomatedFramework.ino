/*
 Name:		FlyAutomatedFramework.ino
 Created:	7/30/2018 2:34:43 PM
 Author:	Gabriel Antoniak
*/

//MS pins on motor driver stepper
const int ms1Pin = 2;	//doubles stepping (1 -> 2, or 4 -> 8)
const int ms2Pin = 3;	//quadruples stepping (1 -> 4)
const int ms3Pin = 11;	//doubles stepping (only from 8 -> 16)

const int readMS1 = 8;
const int readMS2 = 9;
const int readMS3 = 10;

const int stepPin = 4;	//send pulse to move motor
const int dirPin = 5;	//set to high or low to change direction

const int relayLogic1 = 6;	//activate relay 1
const int relayLogic2 = 7;	//activate relay 2

const int can_fr_top_IR = A0;
const int can_fr_bot_IR = A1;
const int can_bk_top_IR = A2;
const int can_bk_bot_IR = A3;

const int con_fr_top_IR = A4;
const int con_fr_bot_IR = A5;
const int con_bk_top_IR = A6;
const int con_bk_bot_IR = A7;

const int align_IR = A8;

int motor1BaseSteps = 400;
int numFlyTubes = 6;

int stepsPerRot;
int stepsToNextFly;
int stepErrorIter;

float error = 0;

int toStep;

void setup() {
	stepsPerRot = findStepsPerRot(motor1BaseSteps);
	stepsToNextFly = findStepsToNextFly(stepsPerRot, numFlyTubes);
	stepErrorIter = findStepErrorIter(stepsToNextFly, stepsPerRot, numFlyTubes);
}

void loop() {
	error = stepMotor(toStep, 400, true, error);
	delay(1000);
}

float findStepErrorIter(int stepsNext, int stepsRot, int numFlies){
	int errorPerFullRot = stepsRot - numFlies*stepsNext;
	float errorIter = ((float) errorPerFullRot) / numFlies;
	return errorIter;
}

int findStepsToNextFly(int stepsPerRot, int numFlyTubes){
	float circRot = 360.0;
	int stepsToFly = floor((circRot / ((float) numFlyTubes)) * ((float) stepsPerRot));
	return stepsToFly;
}

int findStepsPerRot(int baseSteps){
	if (digitalRead(readMS1) == 1)
	{
		baseSteps = baseSteps * 2;
	}

	if (digitalRead(readMS2) == 1){
		baseSteps = baseSteps * 2;
	}

	if (digitalRead(readMS3) == 1){
		baseSteps = baseSteps * 2;
	}

	return baseSteps;
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



float stepMotor(int steps, int speedVal, bool dir, float err){
	chooseMotorDir(dir);
	if (err > 1.0){
		steps = steps + 1;
		err = err - 1.0;
	}
	for (size_t i = 0; i < steps; i++)
	{
		moveMotor(speedVal);
	}
	return err;
}