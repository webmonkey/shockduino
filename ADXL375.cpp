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
  
  pinMode(PIN_SPI_SS, OUTPUT);
  digitalWrite(PIN_SPI_SS, HIGH);

  // Put the ADXL345 into Measurement Mode by writing 0x08 to the POWER_CTL register.
  writeRegister(ADXL375_REG_POWER_CTL, 0x08);  //Measurement mode
}

AccelReading ADXL375::getXYZ()
{
  uint8_t data[6];
  _multiReadRegister(ADXL375_REG_DATAX0, data, 6);

  AccelReading xyz(
    data[0] | data[1]<<8,
    data[2] | data[3]<<8,
    data[4] | data[5]<<8,
    ADXL375_XYZ_READ_SCALE_FACTOR
  );
  
  return xyz;
}

uint8_t ADXL375::readRegister(uint8_t regAddress)
{
  uint8_t data[1];
  _multiReadRegister(regAddress, data, 1);
  return data[0];
}



void ADXL375::_multiReadRegister(uint8_t regAddress, uint8_t values[], uint8_t numberOfBytes)
{
  // Since we're performing a read operation, the most significant bit of the register address should be set.
  regAddress |= 0x80;

  // set the multi-read byte if required
  if (numberOfBytes > 1) {
    regAddress |= 0x40;
  }
  
  // set the Chip select pin low to start an SPI packet.
  digitalWrite(PIN_SPI_SS, LOW);
  // transfer the starting register address that needs to be read.
  SPI.transfer(regAddress);
  
  // read the data
  for(int i=0; i<numberOfBytes; i++){
    values[i] = SPI.transfer(0x00);
  }

  //Set the Chips Select pin high to end the SPI packet.
  digitalWrite(PIN_SPI_SS, HIGH);
}

void ADXL375::writeRegister(uint8_t regAddress, uint8_t value)
{
    //Set Chip Select pin low to signal the beginning of an SPI packet.
  digitalWrite(PIN_SPI_SS, LOW);
  //Transfer the register address over SPI.
  SPI.transfer(regAddress);
  //Transfer the desired register value over SPI.
  SPI.transfer(value);
  //Set the Chip Select pin high to signal the end of an SPI packet.
  digitalWrite(PIN_SPI_SS, HIGH);
}

