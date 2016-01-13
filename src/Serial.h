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

    bool isInitialized() { return initialized; }

private:

    ofSerial mySerial;

    bool initialized = false;

};

#endif //SERIAL_H
