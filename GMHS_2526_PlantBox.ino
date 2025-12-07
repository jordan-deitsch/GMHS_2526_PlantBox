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
	motor1.standby();				// Start motor in standy condition
	
	// Setup I2C bus with 3V3 logic compatability
	Wire.begin();						// Initialize the I2C bus
	pinMode(SDA, INPUT);		// Deactivate 5V pull-up set in Wire.begin()
	pinMode(SCL, INPUT);		// Deactivate 5V pull-up set in Wire.begin()

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

	// Wait 1 sec before repeating loop
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
}