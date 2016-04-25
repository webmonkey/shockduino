#include "Arduino.h"
#include "AccelReading.h"

AccelReading::AccelReading(int16_t _x, int16_t _y, int16_t _z, uint8_t scalingFactor)
{
  x = _x * scalingFactor;
  y = _y * scalingFactor;
  z = _z * scalingFactor;
}

