/*
Programa para el control de un servicio wifi
con un arduino
Recibe tres tipos de ordenes
ON: ENCIENDE LED
OFF: APAGA LED
END: DESCONECTA
*/

#include <SoftwareSerial.h>
#include "wifi.h"           //Parametros de conexión 


#define RXPIN 5
#define TXPIN 4


#define BPS 9600 //Velocidad de comunicaciones
SoftwareSerial wifiSerial (RXPIN,TXPIN);
#include "funciones.h"

int wifi_conected = 1;// orden de reconexión


void setup() 
{
  Serial.begin(BPS);
  wifiSerial.begin(BPS);
  
}

void loop()


{
 
  Serial.println("---------- orden(AT+CWJAP)--");
  orden("AT+CWJAP?");
 
  
  if (wifiSerial.find("ERROR")) 
    {
      Serial.println("encontroado ERROR en CWJAP");
      wifi_conected = 1;
    }

 Serial.print("algortmo: wifi_conected= ");
 Serial.println(wifi_conected);

if(wifi_conected != 0)
  {
      wifi_conected = 0;
      configurarWifi(ordenesAT);  
  }

  configurarWifi(ordenConexion);
  delay(1000);
  enviarPost(ordenPost);
  configurarWifi(ordenClose);
  
  delay(10000);
}




