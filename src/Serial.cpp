#include "Serial.h"

/*
 * Destructor.
 */
Serial::~Serial() {
    mySerial.close();
}

/*
 * Setup the Serial Communication with the Arduino
 */
void Serial::setup(){
    initialized =  mySerial.setup("/dev/ttyACM0", 9600); //open the first device and talk to it at 9600 baud
}


/*
 * Update the acceleromter values coming from the Arduino.
 */
void Serial::updateSerial() {
    while (mySerial.available() > 0) {

        // Get a new byte.
        int message = mySerial.readByte();


        switch (message) {

        case OF_SERIAL_ERROR:
            // something bad happened
            ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
            // bail out
            break;

        case OF_SERIAL_NO_DATA:
            // Nothing was read, try again.
            break;

        case 10: // Newline = end of message. Evaluate.
            {
                string data = buffer; // Convert to string.

                //std::cout << data << std::endl;

                int accelValueTemp = ofToInt(data); // Convert to int.

                accelValue = accelValueTemp / 10;

                //printf("accelValue, %i", accelValue);

                // Reset buffer.
                bufferPosition = 0;
                for (int i = 0; i < bufSize; i++) {
                    buffer[i] = 0; // NULL
                }
            }
            break;

        default: // We have a new byte.
            {
                // Prevent the buffer index from going out of bounds.
                if (bufferPosition >= 10) {
                    bufferPosition = 0;
                }

                // Append the new byte to the buffer.
                buffer[bufferPosition] = (char) message;
                bufferPosition++;
            }
            break;
        }
    }
}
