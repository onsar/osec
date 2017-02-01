

#define BPS 9600 //Velocidad de comunicaciones

#include <SoftwareSerial.h>
#define RXPIN 4
#define TXPIN 5
SoftwareSerial wifiSerialInit (RXPIN,TXPIN);

#include <FaBoLCD_PCF8574.h>
FaBoLCD_PCF8574 lcd;

#include "wifi_basic.h"
WifiBasic wifiBasic(& wifiSerialInit);

#include "temperature_sensor.h"
#include "analog_sensor.h"


void setup(void)
  { 
     Serial.begin(BPS);
     temperatureSensorsBegin();
     
     lcd.begin(16, 2);
     lcd.print(F("hello, FaBo!"));
  }


void loop(void)

  {
      lcd.setCursor(0, 1);
      lcd.print(millis() / 1000);
   
      buildTemperatureMessage();
      analogicalSensorMessage();
      // delay(4000);
  
  }

