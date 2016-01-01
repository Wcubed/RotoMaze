#ifndef SERIAL_H
#define SERIAL_H

#include "ofMain.h"
#include "ofSerial.h"

/*
 * Reads Serial communciation from the Arduino to get the accelerometer values
 */
class Serial
{
public:

    void setup();
    int getAccelerometerValues();

private:

    ofSerial mySerial;

};

#endif //SERIAL_H
