#include "ADXL375.h"

ADXL375 accel;    

void setup(){ 
    Serial.println("hello!");
    Serial.begin(9600);
    accel.init();
    
    accel.setShockThreshold(10);
    accel.startShockDetection();

    Serial.print("Device ID: ");
    Serial.println(accel.readRegister(ADXL375_REG_DEVID), HEX);
    
    Serial.println("initialised");
}

void loop(){

  byte intSource = accel.readRegister(ADXL375_REG_INT_SOURCE);
  if (intSource & 0b01000000) {

    Serial.println("Shock Detected!");

    byte shockStatus = accel.readRegister(ADXL375_REG_ACT_SHOCK_STATUS);

    Serial.print("shockAxes=");
    if (shockStatus & 0b100) Serial.print("x");
    if (shockStatus & 0b010) Serial.print("y");
    if (shockStatus & 0b001) Serial.print("z");
    Serial.println("");

    uint8_t fifoCount = accel.getFIFOBufferSize();

    Serial.println("x\ty\tz\tcombined");

    for (uint8_t i=0; i<fifoCount; i++) {
        accel.getXYZ().printDebug();
    }

    // resets everything
    accel.startShockDetection();
  }
  
  delay(1000);
}
