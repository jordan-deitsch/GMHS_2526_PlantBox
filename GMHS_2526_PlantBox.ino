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
#include "src/tb6612/SparkFun_TB6612.h"
#include "src/bma400/SparkFun_BMA400_Arduino_Library.h"
#include <Wire.h>

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

// Change to set default direction of motor (CW or CCW) instead of switching wires. Value can be 1 or -1
const int offsetA = 1;

// Create a new motor object
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

// Create a new accelerometer sensor object
BMA400 accelerometer;

// I2C address selection
const uint8_t i2cAddress = BMA400_I2C_ADDRESS_DEFAULT; // 0x14

// Functions
void checkMoisture();
void getAccelerometerData();

void setup()
{
	Serial.begin(115200);		// Start serial port to print actions
	Wire.begin();						// Initialize the I2C library
	motor1.standby();				// Start motor in standy condition

	// Check if accelerometer is connected and initialize
	while(accelerometer.beginI2C(i2cAddress) != BMA400_OK)
	{
		Serial.println("Error: BMA400 not connected, check wiring and I2C address!");
		delay(1000);
	}
	Serial.println("BMA400 connected!");

	// TODO: Setup for any other I/O pins: lights? Other controls?
}

void loop()
{
	checkMoisture();
	getAccelerometerData();

	// Wait before taking next moisture measurement
	delay(1000);
}

void checkMoisture()
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
}

void getAccelerometerData()
{
	// Get measurements from the sensor. This must be called before accessing
	// the acceleration data, otherwise it will never update
	accelerometer.getSensorData();

	// Print acceleration data
	Serial.print("Acceleration in g's");
	Serial.print("\t");
	Serial.print("X: ");
	Serial.print(accelerometer.data.accelX, 3);
	Serial.print("\t");
	Serial.print("Y: ");
	Serial.print(accelerometer.data.accelY, 3);
	Serial.print("\t");
	Serial.print("Z: ");
	Serial.println(accelerometer.data.accelZ, 3);

	// Print 50x per second
	delay(20);
}