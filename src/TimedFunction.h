#ifndef TIMED_FUNCTION_H
#define TIMED_FUNCTION_H

#include "MotorDriver.h"
#include "AccelerometerDriver.h"

#define NUM_TIMED_FUNCTIONS (2)

typedef void (*TimedFuctionPtr)();

struct TimedFunction
{
  unsigned long expire_time;
  unsigned long start_time;
  TimedFuctionPtr callback;
};

extern TimedFunction* timed_function_arr[NUM_TIMED_FUNCTIONS];

// Fucntions
void setup_timed_functions();

#endif