/*
 Name:		FlyAutomatedFramework.ino
 Created:	7/30/2018 2:34:43 PM
 Author:	Gabriel Antoniak
*/

#include <math.h>

const int pcbPotPin = A0;
const int pcbRawPin = A1;
const int pcbAlignPin = 3;

const int stepPin = 12;
const int dirPin = 13;

float expectedSteps = 1600.0;
const int numTubes = 8;

volatile bool spinState = true;

char recievedChar;

char startSignal = 'b';

int flyIndex = 0;

enum DeviceCases
{
	listen,
	align,
	fireFly,
	verify,
	suckFly
};

int switchCase = listen;

void setup() {
	pinMode(pcbPotPin, INPUT);
	pinMode(pcbRawPin, INPUT);
	pinMode(pcbAlignPin, INPUT);

	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);

	attachInterrupt(digitalPinToInterrupt(pcbAlignPin), stopSpin, FALLING);

	Serial.begin(9600);

	digitalWrite(dirPin, LOW);
}

void loop() {
	if(switchCase == listen) {
		getFromMATLAB();
		if (recievedChar == startSignal) {
			switchCase = align;
		}
	}

	else if (switchCase == align) {
		float numSteps = alignCartridge();
		flyIndex = (flyIndex + round(numSteps / expectedSteps)) % numTubes;
		
		if (numSteps < 100) {
			switchCase = align; //Too few steps, keep going
		}
		else {
			switchCase = fireFly;
		}
	}

	else if (switchCase == fireFly) {
		delay(1000);
		switchCase = verify;
	}

	else if (switchCase == verify) {
		delay(1000);
		switchCase = suckFly;
	}

	else if (switchCase == suckFly) {
		delay(1000);
		switchCase = listen;
	}

	else {
		delay(1000);
	}
}

void stopSpin() {
	spinState = false;
}

void sendStep(int val1, int val2) {
	digitalWrite(stepPin, HIGH);
	delayMicroseconds(val1);
	digitalWrite(stepPin, LOW);
	delayMicroseconds(val2);
}

float alignCartridge() {
	digitalWrite(dirPin, LOW);
	float steps = 0;
	while (spinState) {
		sendStep(10, 300);
		steps++;
	}

	spinState = true;
	return steps;
}

void getFromMATLAB() {
	if (Serial.available() > 0) {
		recievedChar = Serial.read();
	}
}

void sendToMATLAB(char message) {
	Serial.println(message);
}