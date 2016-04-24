#include "Arduino.h"
#include "ADXL375.h"
#include "SPI.h"

ADXL375::ADXL375()
{
}

void ADXL375::init()
{
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);  
}

AccelReading ADXL375::getXYZ()
{
  AccelReading xyz(1,2,3);
  return xyz;
}

uint8_t ADXL375::readRegister(uint8_t reg)
{
  return 123;  
}

void ADXL375::writeRegister(uint8_t reg, uint8_t value)
{
  // do nothing
}

