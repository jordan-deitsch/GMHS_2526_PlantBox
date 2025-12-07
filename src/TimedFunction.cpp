#include "TimedFunction.h"

// Available timed functions
static TimedFunction check_moisture;
static TimedFunction check_accelerometer;
static TimedFunction toggle_lights;
static TimedFunction toggle_fan;

static const unsigned long CHECK_MOISTURE_TIME = 1000UL * 60 * 5; // Check moisture every 5 minutes
static const unsigned long CHECK_GRAVITY_TIME = 1000UL * 10; // Check moisture every 10 seconds

TimedFunction* timed_function_arr[NUM_TIMED_FUNCTIONS];

void setup_timed_functions()
{
  check_moisture.expire_time = CHECK_MOISTURE_TIME;
  check_moisture.start_time = millis();
  check_moisture.callback = &MotorDriver_check_moisture;

  check_accelerometer.expire_time = CHECK_GRAVITY_TIME;
  check_accelerometer.start_time = millis();
  check_accelerometer.callback = &AccelerometerDriver_check_gravity;

  timed_function_arr[0] = &check_moisture;
  timed_function_arr[1] = &check_accelerometer;
}

void check_timed_functions()
{
  unsigned long current_time = millis();
  for(int i=0; i<NUM_TIMED_FUNCTIONS; i++){
    if((current_time - timed_function_arr[i]->start_time) >= timed_function_arr[i]->expire_time) {
      timed_function_arr[i]->callback();            // Perform callback when time is reached
      timed_function_arr[i]->start_time = millis(); // Reset start time at end of performing callback
    }
  }
}
