#ifndef ACCELEROMETER_DRIVER_H
#define ACCELEROMETER_DRIVER_H

#include "bma400/SparkFun_BMA400_Arduino_Library.h"

// I2C address selection for BMA400
const uint8_t i2cAddress = BMA400_I2C_ADDRESS_DEFAULT; // 0x14

// Declare a new accelerometer sensor object
extern BMA400 accelerometer;

// Functions
void AccelerometerDriver_check_gravity();


#endif