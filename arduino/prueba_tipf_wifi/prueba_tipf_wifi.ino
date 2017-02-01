

#include <SoftwareSerial.h>
#define RXPIN 4
#define TXPIN 5
#define BPS 9600 //Velocidad de comunicaciones
SoftwareSerial wifiSerialInit (RXPIN,TXPIN);

#include "wifi_basic.h"
// Para utilizar wifi en temperaturSensor18b20
WifiBasic wifiBasic(& wifiSerialInit);


#include "temperature_sensor.h"

#include "sensor_configuration.h"

// include the library code:
#include <Wire.h>
#include <FaBoLCD_PCF8574.h>
// initialize the library
FaBoLCD_PCF8574 lcd;



void setup(void)
{ 
    Serial.begin(9600);
    // setupWifi(wifi_m);
    temperatureSensorsBegin();

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(F("hello, FaBo!"));

    
}


void loop(void)

{



    // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);


  
    buildTemperatureMessage();
    analogicalSensorMessage();
    // delay(4000);

}

