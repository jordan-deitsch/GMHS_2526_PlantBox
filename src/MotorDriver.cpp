#include "MotorDriver.h"

// Constants for moisture sensor and motor operation (UPDATE FOR YOUR DESIGN)
static const int MOISTURE_THRESHOLD = 150;  // Threshold for moisture sensor to trigger motor, between [0, 255]
static const int MOTOR_SPEED = 100;		      // Default speed of motor, between [0, 255]
static const int MOTOR_ON_TIME_SEC = 1;			// Deafult ON time of motor when activated (seconds)
static const int MOTOR_MAX_TIME_SEC = 100;  // Maximum time the motor can spin before screw is fully extended (seconds)
static const int offsetA = 1;               // Set default direction of motor (CW or CCW). Value can be 1 or -1

// Define local variables
static int moisture_value = 0;		// Measured value from analog input of moisture sensor
static int motor_active_time = 0;	// Track active time of motor to know how far lead screw is extended

// Constructor for motor
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

void MotorDriver_check_moisture()
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
