#include "TimedFunction.h"

// Available timed functions
static TimedFunction tf_check_moisture;
static TimedFunction tf_check_accelerometer;
static TimedFunction tf_toggle_lights;
static TimedFunction tf_toggle_fan;

static const unsigned long CHECK_MOISTURE_TIME = 1000UL * 60 * 5; // Check moisture every 5 minutes
static const unsigned long CHECK_GRAVITY_TIME = 1000UL * 10; // Check gravity every 10 seconds

TimedFunction* timed_function_arr[NUM_TIMED_FUNCTIONS];

void setup_timed_functions()
{
  tf_check_moisture.expire_time = CHECK_MOISTURE_TIME;
  tf_check_moisture.start_time = millis();
  tf_check_moisture.callback = &MotorDriver_check_moisture;
  timed_function_arr[0] = &tf_check_moisture;

  tf_check_accelerometer.expire_time = CHECK_GRAVITY_TIME;
  tf_check_accelerometer.start_time = millis();
  tf_check_accelerometer.callback = &AccelerometerDriver_check_gravity;
  timed_function_arr[1] = &tf_check_accelerometer;
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
