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

    ~Serial();

    void setup();
    int getAccelValue() { return accelValue; }

    void updateSerial();

    bool isInitialized() { return initialized; }

private:

    static const int bufSize = 10;

    ofSerial mySerial;

    bool initialized = false;

    char buffer[bufSize]; // Buffer to remember half messages between frames.
    int bufferPosition;

    int accelValue;
};

#endif //SERIAL_H
