/*
  This is an Example for the FaBo LCD I2C Brick.

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 compatible library 23 Mar 2016
 by Hideki Yamauchi

 This example code is in the public domain.

 http://fabo.io/212.html
 */

// include the library code:
#include <Wire.h>
#include <FaBoLCD_PCF8574.h>

// initialize the library
FaBoLCD_PCF8574 lcd;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, FaBo!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}

