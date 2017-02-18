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

uint32_t t_last_tx=0;
uint32_t t_last_lcd=0;

void setup(void)


  { 
     Serial.begin(BPS);
     temperatureSensorsBegin();
     
     lcd.begin(16, 2);
     lcd.print(F("Hola, ENDEF!"));
  }


void loop(void)

  {

      buildTemperatureMessage(1);
      // analogicalSensorMessage(1);
 


    
  
  }

