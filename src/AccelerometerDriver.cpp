#include "AccelerometerDriver.h"

BMA400 accelerometer;

void AccelerometerDriver_check_gravity()
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