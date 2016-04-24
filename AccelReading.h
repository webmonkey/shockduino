#ifndef AccelReading_h
#define AccelReading_h

#include "Arduino.h"

class AccelReading
{
  public:
    AccelReading(int x, int y, int z);
    int x;
    int y;
    int z;
};

#endif
