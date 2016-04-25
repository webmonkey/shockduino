#include "ADXL375.h"

ADXL375 accel;    

void setup(){ 
    Serial.println("hello!");
    Serial.begin(9600);
    accel.init();
    Serial.println("initialised");
}

void loop(){

    AccelReading xyz = accel.getXYZ();

    // print in output that the serial plotter can use
    Serial.print(xyz.x);
    Serial.print("\t");
    Serial.print(xyz.y);
    Serial.print("\t");
    Serial.println(xyz.z);
    
    delay(10);
}
