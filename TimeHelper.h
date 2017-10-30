#ifndef TIMEHELPER_H
#define TIMEHELPER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class TimeHelper {

public:
  static void setTime(unsigned long ts);

  static bool timeIsSet();
  
private:
  static bool timeSet;
};

#endif
