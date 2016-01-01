/*
 ADXL3xx

 Reads an Analog Devices ADXL3xx accelerometer and communicates the
 acceleration to the computer.  The pins used are designed to be easily
 compatible with the breakout boards from Sparkfun, available from:
 http://www.sparkfun.com/commerce/categories.php?c=80

 http://www.arduino.cc/en/Tutorial/ADXL3xx

 The circuit:
 analog 3: x-axis

 created 2 Jul 2008
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

*/

// these constants describe the pins. They won't change:
const int xpin = A0;                  // x-axis of the accelerometer
// Connect the SLP (sleep) pin to 3.3v or 5v !!!

int xscaled;
int scale = 180; //The variable scale is set to the full scale of the accelerometer measured in g forces. It is set to 3 for the ADXL337 and set to 200 for the ADXL377, since the sensors measure a ±3g and ±200g range respectively.

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
}

void loop() {
  // print the sensor values:
  int valx = analogRead(0);
  valx = map(valx, 0, 675, -scale, scale); // 3.3/5 * 1023 =~ 675
  Serial.println(valx); //Send "B" to indicate the beginning and "E" to indicate the end of the values that needs to be send
  
  delay(100);
}
