/******************************************************************************
GMHS_2526_PlantBox.ino
Arduino controller for plant box sensors and motors

Modified from:
TB6612FNG H-Bridge Motor Driver Example code
Michelle @ SparkFun Electronics
8/20/16
https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library

Uses 1 motor and 1 moisture sensor to add moisture to a plant grow-bed.
Activate the motor for a finite time when the moisture drops below a 
minimum threshold to extend lead screw. Retract the motor lead screw 
when fully extended to allow for removal/replacement of water bag.

Resources:
TB6612 SparkFun Library
******************************************************************************/

// This is the library for the TB6612 that contains the Motor class and functions
#include "SparkFun_TB6612.h"

// Motor driver digital pins (UPDATE FOR YOUR DESIGN)
#define AIN1 (8)
#define AIN2 (9)
#define PWMA (10)	// Must be a PWM supported pin (~)
#define STBY (11)

// Moisture sensor analog input pin (UPDATE FOR YOUR DESIGN)
#define MOISTURE_SENSOR (A0)
// TODO: Add more sensor definitions as needed (temperature, humidity, etc.)

// Constants for moisture sensor and motor operation (UPDATE FOR YOUR DESIGN)
const int MOISTURE_THRESHOLD 		= 150; 		// Threshold for moisture sensor to trigger motor, between [0, 255]
const int MOTOR_SPEED 					= 100;		// Default speed of motor, between [0, 255]
const int MOTOR_ON_TIME_SEC 		= 1;			// Deafult ON time of motor when activated (seconds)
const int MOTOR_MAX_TIME_SEC 		= 100;  	// Maximum time the motor can spin before screw is fully extended (seconds)
const int MEASUREMENT_DELAY_MIN	= 1;			// Delay time before checking moisture sensor each loop (minutes)

// Define variables used in main loop
int moisture_value = 0;		// Measured value from analog input of moisture sensor
int motor_active_time = 0;	// Track active time of motor to know how far lead screw is extended
unsigned long measure_delay_time = 60*1000*MEASUREMENT_DELAY_MIN;	// Convert delay time to msec

// Change to set default direction of motor (CW or CCW) instead of switching wires. Value can be 1 or -1
const int offsetA = 1;

// Initialize motor with board pin numbers
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);


void setup()
{
	Serial.begin(9600);		// Start serial port to print actions
	motor1.standby();			// Start motor in standy condition

	// TODO: Setup for any other I/O pins: lights? Other controls?
}


void loop()
{
	// Read moisture sensor value
	moisture_value = analogRead(MOISTURE_SENSOR);
	Serial.print("Moisture Level: ");
	Serial.println(moisture_value);

	// Check if sensor is below desired moisture threshold
	if(moisture_value < MOISTURE_THRESHOLD) {
		Serial.println("--> RUNNING MOTOR");
		motor1.drive(MOTOR_SPEED, 1000*MOTOR_ON_TIME_SEC);
		motor1.brake();
		motor_active_time += MOTOR_ON_TIME_SEC;	// Increment tracker for active motor time
	}

	// Check if motor has reached its maximum active time (screw is fully extended)
	if(motor_active_time > MOTOR_MAX_TIME_SEC) {
		Serial.println("--> REVERSING MOTOR");
		motor1.drive(-1*MOTOR_SPEED, 1000*motor_active_time);	// Use negative speed for reverse
		motor1.brake();
		motor_active_time = 0;	// Reset active time tracker after motor returned to starting position
	}

	// Wait for the desired time before taking  next moisture measurement
	measure_delay_time = 1000;	// TEMPORARY: loop every second during testing to speed up development
	delay(measure_delay_time);
}