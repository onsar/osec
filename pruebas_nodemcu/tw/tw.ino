
#include <ESP8266WiFi.h>

#include "wifi_x_esp.h"

#include "temperature_sensor.h"


void setup()
  {
    
    Serial.begin(115200);
    Serial.println();
    wifi_conection();
    temperatureSensorsBegin();
    delay(3000);

  }



void loop() 
  {
    
    buildTemperatureMessage(2);
  
  }


  
