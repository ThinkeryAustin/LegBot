// LegBot obstacle avoiding Robot
// The LegBot was modeled after the inchworm bot here, with an Arduino and Ping sensor added:
// http://www.instructables.com/id/Simple-Bots-Inchworm/
//  Ken Sharp, Oct 2014

#include <Servo.h>

// Pin Mapping
const int motorPin = 10;
const int pingEchoPin = 7;
const int pingTrigPin = 8;
const int switchPin = 2;

// There's a good chance this will have to be changed to "LOW"
// based on how the switch is wired to the Arduino.
const int switchPolarity = HIGH;

// Set the speed that the servo will move.
// Range is 0-90 with higher numbers meaning the servo will move faster.
const int motorSpeed = 15;

// Threshold for obstacles (in cm)
const int dangerThreshold = 10;

Servo motor;
int currentMotorSpeed;

void setup() {
	// Init main servo
	motor.attach(motorPin);
	
	// Init switch input and enable pullup resistor
	pinMode(switchPin, INPUT_PULLUP);
	
	// Init pins for rangefinder sensor
	pinMode(pingTrigPin, OUTPUT);
	pinMode(pingEchoPin, INPUT);
	
	delay(5000);
}

void loop() {
	int fwdDistance = ping();

	if (fwdDistance < dangerThreshold) {
		// stop the motor, there's an obstacle in our way
		if (currentMotorSpeed != 90) {
			currentMotorSpeed = 90;
			motor.write(90);
		}
	}
	else if (digitalRead(switchPin) == switchPolarity) {
		// if the switch has not flipped yet, keep going forward
		if (currentMotorSpeed != 90 + motorSpeed) {
			currentMotorSpeed = 90 + motorSpeed;
			motor.write(currentMotorSpeed);
		}
	}
	else {
		// after the switch flips move backward
		if (currentMotorSpeed != 90 - motorSpeed) {
			currentMotorSpeed = 90 - motorSpeed;
			motor.write(currentMotorSpeed);
		}
	}
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