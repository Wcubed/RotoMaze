#include "Serial.h"

/*
 * Setup the Serial Communication with the Arduino
 */
void Serial::setup(){
    initialized =  mySerial.setup("/dev/ttyACM0", 9600); //open the first device and talk to it at 9600 baud
}

/*
 * Update the acceleromter values coming from the Arduino
 */
int Serial::getAccelerometerValues() {

    // we want to read 15 bytes
    int bytesRequired = 32;
    unsigned char bytes[bytesRequired];
    int bytesRemaining = bytesRequired;

    // loop until we've read everything
    while ( bytesRemaining > 0 )
    {
        // check for data
        if ( mySerial.available() > 0 )
        {
            unsigned char bytesReturned[32];
            memset(bytesReturned, 0, 32);

            // read from the serial port
            mySerial.readBytes(bytesReturned, 32);

            string serialData = (char*) bytesReturned; // cast to char
            printf("d %c \n", ofToChar(serialData));

            int rotaryValue = ofToInt(serialData);
            //printf("rotaryValue %i", rotaryValue);
            if (rotaryValue != 0) return rotaryValue;

            // try to read - note offset into the bytes[] array, this is so
            // that we don't overwrite the bytes we already have
            int bytesArrayOffset = bytesRequired - bytesRemaining;
            int result = mySerial.readBytes( &bytes[bytesArrayOffset],
                                             bytesRemaining );

            // check for error code
            if ( result == OF_SERIAL_ERROR )
            {
                // something bad happened
                ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
                // bail out
                break;
            }
            else if ( result == OF_SERIAL_NO_DATA )
            {
                // nothing was read, try again
            }
            else
            {
                // we read some data!
                bytesRemaining -= result;
            }
        }
    }
}
