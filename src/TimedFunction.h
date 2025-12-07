#ifndef TIMED_FUNCTION_H
#define TIMED_FUNCTION_H

#define NUM_TIMED_FUNCTIONS (2)

typedef struct TimedFunction
{
  unsigned long expire_time;
  unsigned long start_time;
  void* function_ptr;
};

// Available timed functions
TimedFunction check_moisture;
TimedFunction check_accelerometer;
TimedFunction toggle_lights;
TimedFunction toggle_fan;

TimedFunction* timed_function_arr[NUM_TIMED_FUNCTIONS];

#endif