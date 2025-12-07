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

Use I2C accelerometer to detect changes in gravity and when plant box 
is in null-gravity environment.  

Resources:
TB6612 SparkFun Library
BMA400 SparkFun Library
******************************************************************************/

// This is the library for the TB6612 that contains the Motor class and functions
#include "src/MotorDriver.h"
#include "src/AccelerometerDriver.h"
#include "src/TimedFunction.h"
#include <Wire.h>

void setup()
{
	Serial.begin(115200);		// Start serial port
	Wire.begin();						// Initialize the I2C library
	motor1.standby();				// Start motor in standy condition

	// Check if accelerometer is connected and initialize
	while(accelerometer.beginI2C(i2cAddress) != BMA400_OK)
	{
		Serial.println("Error: BMA400 not connected, check wiring and I2C address!");
		delay(1000);
	}
	Serial.println("BMA400 connected!");

	// TODO: Setup for any other I/O pins: lights? fan? Other controls?

	setup_timed_functions();
}


void loop()
{
	check_timed_functions();
}