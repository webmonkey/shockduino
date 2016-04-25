#include "ADXL375.h"

ADXL375 accel;    

void setup(){ 
    Serial.println("hello!");
    Serial.begin(9600);
    accel.init();
    Serial.println("initialised");
}

void loop(){

    Serial.println("looping...");

    int val = accel.readRegister(ADXL375_REG_DEVID);
    Serial.println(val);

    AccelReading xyz = accel.getXYZ();

    Serial.print("x=");
    Serial.print(xyz.x);
    Serial.print(",y=");
    Serial.print(xyz.y);
    Serial.print(",z=");
    Serial.println(xyz.z);
    
    delay(1000);
}
