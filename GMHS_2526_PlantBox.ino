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

	// Setup all timed functions with expiration timer and callback
	setup_timed_functions();
}

void loop()
{
	check_timed_functions();
}