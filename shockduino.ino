#include "ADXL375.h"
#include "RFduinoBLE.h"


ADXL375 accel;

// size of shock to look for in g
const uint16_t SHOCKDUINO_THRESHOLD = 10;

// count of number of shocks won't persist power cycling
uint8_t shockCount;

void setup(){ 
    Serial.println("hello!");
    Serial.begin(9600);
    accel.init();

    // shock could be between 2 axis
    accel.setShockThreshold(SHOCKDUINO_THRESHOLD / 2);
    shockCount=0;
    accel.startShockDetection();

    // setup the iBeacon
    RFduinoBLE.iBeacon = true;
    RFduinoBLE.iBeaconMajor = shockCount;
    RFduinoBLE.begin();

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

    uint8_t maxAccelSize = getMaxAcceleration(accel);
    if (maxAccelSize>=SHOCKDUINO_THRESHOLD) {
        Serial.print("maxAccelSize=");
        Serial.println(maxAccelSize);
        shockCount++;
        RFduinoBLE.iBeaconMajor = shockCount;
        RFduinoBLE.end();
        RFduinoBLE.begin();
    } else {
        Serial.println("too small!");
    }




    // resets everything
    accel.startShockDetection();
  }
  
  delay(1000);
}

// goes through the accellerometer's FIFO buffer and returns the largest shock
uint8_t getMaxAcceleration(ADXL375 accellerometer)
{
    uint8_t fifoCount = accellerometer.getFIFOBufferSize();
    uint32_t maxAccel=0;
    for (uint8_t i=0; i<fifoCount; i++) {
        uint32_t thisAccel = accel.getXYZ().accelSize();
        if (thisAccel>maxAccel) maxAccel=thisAccel;
    }
    return (uint8_t) (maxAccel / 1000);
}

