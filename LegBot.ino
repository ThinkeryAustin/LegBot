// LegBot obstacle avoiding Robot
// The LegBot was modeled after the inchworm bot here, with an Arduino and Ping sensor added:
// http://www.instructables.com/id/Simple-Bots-Inchworm/
//  Ken Sharp, Oct 2014

#include <Servo.h>

// Pin Mapping
const int motorPin = 10;
const int pingEchoPin = 7;
const int pingTrigPin = 8;

// Set the angles of the two positions that the bot uses to move
const int motorOpenPosition = 90;
const int motorClosedPosition = 60;

// time to wait between "steps" of the bot, in milliseconds
// this increases or decreases the overall speed of the bot
const int motorStepDelay = 2000;

// Threshold for obstacles (in cm)
const int dangerThreshold = 10;

Servo motor;

void setup() {
	// Init main servo
	motor.attach(motorPin);
	
	// Init pins for rangefinder sensor
	pinMode(pingTrigPin, OUTPUT);
	pinMode(pingEchoPin, INPUT);
	
	delay(5000);
}

void loop() {
	int fwdDistance = ping();
	int currentPos = 0;

	if (fwdDistance > dangerThreshold) {
		// keep going, there's no obstruction
		if (!currentPos) {
			motor.write(motorOpenPosition);
			currentPos = 1;
		}
		else {
			motor.write(motorClosedPosition);
			currentPos = 0;
		}
	}
	
	// wait until the next step
	delay(motorStepDelay);
}

long ping()
{
	int duration;
	
	// Send out PING))) signal pulse
	digitalWrite(pingTrigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(pingTrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(pingTrigPin, LOW);

	//Get duration it takes to receive echo
	duration = pulseIn(pingEchoPin, HIGH);

	//Convert duration into distance
	return duration / 29 / 2;
}