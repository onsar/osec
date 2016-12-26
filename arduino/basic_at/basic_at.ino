/*
Programa para el control de un servicio wifi
con un arduino
Recibe tres tipos de ordenes
ON: ENCIENDE LED
OFF: APAGA LED
END: DESCONECTA
*/

#include <SoftwareSerial.h>
#include "wifi.h"//Parametros de conexión 

#define RXPIN 4
#define TXPIN 5

#define LEDPIN 13

#define BPS 9600 //Velocidad de comunicaciones
SoftwareSerial wifiSerial (RXPIN,TXPIN);

#include "funciones.h"

void setup() 
{
  pinMode(LEDPIN,OUTPUT);
  digitalWrite(LEDPIN,LOW);
  Serial.begin(BPS);
  wifiSerial.begin(BPS);
  //Llamada a las funcioes para configurar la conexión wifi
  configurarWifi(ordenesAT);
  delay(2000);
  //enviar datos
  configurarWifi(ordenConexion);
  enviarPost(ordenPost);
  configurarWifi(ordenClose);
}

void loop()
{//funcion que recibe el mensaje que ha llegado por la wifi
  configurarWifi(ordenConexion);
  enviarPost(ordenPost);
  configurarWifi(ordenClose);
  delay(10000);
}
