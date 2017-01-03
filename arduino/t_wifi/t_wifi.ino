

#include <SoftwareSerial.h>
#define RXPIN 5
#define TXPIN 4
#define BPS 9600 //Velocidad de comunicaciones
SoftwareSerial wifiSerialInit (RXPIN,TXPIN);

#include "wifi_basic.h"
// Para utilizar wifi en temperaturSensor18b20
WifiBasic wifiBasic(& wifiSerialInit);


#include "temperature_sensor.h"


void setup(void)
{ 
    Serial.begin(9600);
    // setupWifi(wifi_m);
    temperatureSensorsBegin();
}


void loop(void)
{
    buildTemperatureMessage();
    delay(2000);

}

