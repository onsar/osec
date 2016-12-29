

#include <SoftwareSerial.h>
// #include "wifi.h"           //Parametros de conexión 


#define RXPIN 5
#define TXPIN 4


#define BPS 9600 //Velocidad de comunicaciones
SoftwareSerial wifiSerial (RXPIN,TXPIN);
#include "funciones.h"




void setup() 
{
  Serial.begin(BPS);
  wifiSerial.begin(BPS);
  
}

void loop()


{
 
  sendTemperatureMessage();

  
  delay(10000);
}




