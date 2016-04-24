#include "Arduino.h"
#include "AccelReading.h"

AccelReading::AccelReading(int _x, int _y, int _z)
{
  x = _x;
  y = _y;
  z = _z;
}

