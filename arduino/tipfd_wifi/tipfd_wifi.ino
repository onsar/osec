
#define BPS 9600 //Velocidad de las comunicaciones

#include <SoftwareSerial.h>
#define RXPIN 6
#define TXPIN 5
SoftwareSerial wifiSerialInit (RXPIN,TXPIN);

#include "wifi_basic.h"
WifiBasic wifiBasic(& wifiSerialInit);

#include <FaBoLCD_PCF8574.h>
FaBoLCD_PCF8574 lcd;

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
    uint32_t current_time= millis();
    
    if ((current_time - t_last_tx) > 300000)
      {      
        Serial.print(F("************Print WIFI + LCD - sgs: "));
        t_last_tx = current_time;
        Serial.println(millis() / 1000);
        buildTemperatureMessage(0);
        analogicalSensorMessage(0);
      }

    // if ((current_time - t_last_lcd) > 20000)
      {     
        Serial.print(F("************Print LCD - sgs: "));
        t_last_lcd = current_time;
        Serial.println(millis() / 1000);
        buildTemperatureMessage(1);
        analogicalSensorMessage(1);
      }
  }
  
