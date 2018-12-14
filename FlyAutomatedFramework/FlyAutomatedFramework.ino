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
		Serial.println("Listening");
		delay(2500);
		switchCase = align;
	}
	else if (switchCase == align) {
		Serial.println("Aligning");
		float numSteps = alignCartridge();
		flyIndex = (flyIndex + round(numSteps / expectedSteps)) % numTubes;
		
		if (numSteps < 100) {
			switchCase = align;
		}
		else {
			switchCase = fireFly;
		}
	}
	else if (switchCase == fireFly) {
		Serial.println("Firing");
		delay(1000);
		switchCase = verify;
	}
	else if (switchCase == verify) {
		Serial.println("Verifying");
		delay(1000);
		switchCase = suckFly;
	}
	else if (switchCase == suckFly) {
		Serial.println("Sucking");
		delay(1000);
		switchCase = listen;
	}
	else {
		Serial.println("Whoops, what happened?");
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