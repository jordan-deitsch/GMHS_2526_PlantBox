#include "TimedFunction.h"

// Available timed functions
static TimedFunction check_moisture;
static TimedFunction check_accelerometer;
static TimedFunction toggle_lights;
static TimedFunction toggle_fan;

TimedFunction* timed_function_arr[NUM_TIMED_FUNCTIONS];


void setup_timed_functions()
{
  check_moisture.expire_time = 0;
  check_moisture.start_time = millis();
  check_moisture.callback = &MotorDriver_check_moisture;

  check_accelerometer.expire_time = 0;
  check_accelerometer.start_time = millis();
  check_accelerometer.callback = &AccelerometerDriver_check_gravity;

  timed_function_arr[0] = &check_moisture;
  timed_function_arr[1] = &check_accelerometer;
}
