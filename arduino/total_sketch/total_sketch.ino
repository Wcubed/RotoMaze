/*
  LiquidCrystal Library - display() and noDisplay()

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD and uses the
 display() and noDisplay() functions to turn on and off
 the display.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay

 */
 
 /*
 ADXL3xx

 Reads an Analog Devices ADXL3xx accelerometer and communicates the
 acceleration to the computer.  The pins used are designed to be easily
 compatible with the breakout boards from Sparkfun, available from:
 http://www.sparkfun.com/commerce/categories.php?c=80

 http://www.arduino.cc/en/Tutorial/ADXL3xx

  The circuit:
 * ACE VCC pin to 3.3V
 * ACE GND pin to GND
 * ACE ZOUT pin to analog pin A0
 * ACE YOUT pin to analog pin A1
 * ACE XOUT pin to analog pin A2
 * ACE SLP pin to GND

 created 2 Jul 2008
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

*/

//// LCD
// include the library code LCD screen:
#include <LiquidCrystal.h>

//// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//// Serial data
String str;

//// Accelerometer
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)
int scale = 1800;                 //The variable scale is set to the full scale of the accelerometer measured in g forces. It is set to 3 for the ADXL337 and set to 200 for the ADXL377, since the sensors measure a ±3g and ±200g range respectively.

int sensVal;           // for raw sensor values 
float filterVal;       // this determines smoothness  - .0001 is max  1 is off (no smoothing)
float smoothedVal;     // this holds the last loop value just use a unique variable for every different sensor that needs smoothing
float smoothedVal2;   // this would be the buffer value for another sensor if you needed to smooth two different sensors - not used in this sketch
int i;              // loop counters or demo   

int zvalue_old;                  // z-axis (only on 3-axis models)
int zvalue;
int zcount;
int zdifference;

void setup() {
  // Set up serial
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  //LED
  pinMode(13, OUTPUT);
}

void loop() {
  //// Serial communication  
    // send data only when you receive data:
        if (Serial.available() > 0) {
                // Clear things displayed on screen
                lcd.clear();
            
                // read the incoming byte:
                str = Serial.readString();
                
                // say what you got:
                //Serial.print("I received: ");
                //Serial.println(str);
                
                char charBuf[33];
                str.toCharArray(charBuf, 33);
                
                
                if (arrayIncludeElement(charBuf, 'n')){
                   //Serial.print("Found an number:");
                   for (int i = 1; i < strlen(charBuf); i++) {
                    //Serial.println(charBuf[i]);
                    lcd.print(charBuf[i]);
                    digitalWrite(13, LOW);   // turn the LED off (HIGH is the voltage level)
                 }
                }
                
                if (arrayIncludeElement(charBuf, 't')){
                   lcd.clear();
                   lcd.setCursor(0, 0);
                   lcd.print("Correct");
                   lcd.setCursor(0, 1);
                   lcd.print("Goed gedaan!");
                   lcd.setCursor(0, 0);
                   //Serial.println("CORRECT");
                   digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                }
                
                if (arrayIncludeElement(charBuf, 'f')){
                   lcd.clear();
                   lcd.setCursor(0, 0);
                   lcd.print("Verkeerd");
                   lcd.setCursor(0, 1);
                   lcd.print("Probeer opnieuw!");
                   lcd.setCursor(0, 0);
                   digitalWrite(13, LOW);   // turn the LED off (HIGH is the voltage level)
                   //Serial.println("WRONG");
                }
                
                if (arrayIncludeElement(charBuf, '@')){
                   lcd.clear();
                   for (int i = 1; i < strlen(charBuf); i++) {
                    //Serial.println(charBuf[i]);
                    lcd.print(charBuf[i]);
                 }
                   //Serial.println("TEXT");
                }
                
                if (arrayIncludeElement(charBuf, '#')){
                   lcd.setCursor(0, 0);
                   lcd.print("We hebben je");
                   lcd.setCursor(0, 1);
                   lcd.print("nodig! Doe mee!");
                   /*for (int i = 1; i < strlen(charBuf); i++) {
                    //Serial.println(charBuf[i]);
                     lcd.print(charBuf[i]);
                   }*/
                   lcd.setCursor(0, 0);
                 
                    digitalWrite(13, HIGH);
                    delay(500);
                    digitalWrite(13, LOW);
                    delay(500);
                    digitalWrite(13, HIGH);
                    delay(500);
                    digitalWrite(13, LOW);
                    delay(500);
                    digitalWrite(13, HIGH);
                    delay(500);
                    digitalWrite(13, LOW);
                    delay(500);
                    digitalWrite(13, HIGH);
                    delay(500);
                    digitalWrite(13, LOW);
                    delay(500);
                    digitalWrite(13, HIGH);
                    delay(500);
                    digitalWrite(13, LOW);
                    delay(500);
                    digitalWrite(13, HIGH);
                    delay(500);
                    digitalWrite(13, LOW);
                    delay(500);
                    digitalWrite(13, HIGH);
                    delay(500);
                    digitalWrite(13, LOW);
                    delay(500);
                    digitalWrite(13, HIGH);
                    delay(500);
                    digitalWrite(13, LOW);
                    delay(500);
                   //Serial.println("TEXT");
                }
        }
        
   // i < 250 for slow response
   for (i = 0; i < 250; i++){    // substitute some different filter values
    filterVal = i * .15; 

      sensVal = analogRead(xpin);   //this is what one would do normally
      smoothedVal =  smooth(sensVal, filterVal, smoothedVal);   // second parameter determines smoothness  - 0 is off,  .9999 is max smooth 

      //Serial.print(sensVal);
      //Serial.print("   ");
      //Serial.println(smoothedVal, DEC);
      int mapValX = map(smoothedVal, 0, 675, -scale, scale); // 3.3/5 * 1023 =~ 675
      Serial.println(mapValX);
      //Serial.print("      ");
      //Serial.print("filterValue * 100 =  ");   // print doesn't work with floats
      //Serial.println(filterVal * 100, DEC);
      
      //delay(30);
}
    
}

////Functions
 boolean arrayIncludeElement(char* array, char element) {
   for (int i = 0; i < strlen(array); i++) {
      //Serial.println(array[i]);
      if (array[i] == element) {
        return true;
      }
   }
   return false;
}


int smooth(int data, float filterVal, float smoothedVal){


  if (filterVal > 1){      // check to make sure param's are within range
    filterVal = .99;
  }
  else if (filterVal <= 0){
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (int)smoothedVal;
}
