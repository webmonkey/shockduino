# shockduino
Shock detection and reporting device

## Synposis

The idea is to create a small device that you can include in a package/parcel sent via the post. 
 
The device will be capable of detecting shock/drop events. Before signing for the parcel at the other end you can see if it's been dropped or not.

## Hardware

Initially using an RFduino and an ADXL375 accelerometer

## Project Plan

### Prototype Hardware

- [ ] Connect up hardware and verify it works

### Prototype Software

- [ ] Pull meaningful data from the ADXL375
- [ ] Separate out ADXL375 functionality into a library
- [ ] Implement shock detection on the ADXL375
- [ ] Calculate shock amplitude after a shock event is triggered
- [ ] Get iBeacon reporting of shocks working
- [ ] Get RFduino sleep mode and interrupt on shock event working
- [ ] Get INACT/ACT detection working with ADXL375
- [ ] Configure iBeacon to only advertise when the ADXL375 is active
