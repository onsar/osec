

/*****************************/
/******** CONFIGURACION ******/
/*****************************/

#define LOGIN "casaelobrero"
#define PASSWORD "lacosamasbonitadelmundo"
#define IP_SERVER "192.168.1.141"
#define PORT_SERVER 7000


/*****************************/

#include <ESP8266WiFi.h>
WiFiClient client;

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance

const int AnalogIn  = A0;
int readingIn = 0;


String agent = "prueba";
String name = "Intensidad";
int value = 0;
int bucle = 0;


void setup()
  {
    Serial.begin(115200);
    Serial.println();
  
    WiFi.begin(LOGIN, PASSWORD);
    
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }
    Serial.println();
    
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());


    emon1.current(A0,31.4);             // Current: input pin, calibration.
  }



void loop() 
  {

    double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  
    Serial.print(Irms*230.0);         // Apparent power
    Serial.print(" ");
    Serial.println(Irms);          // Irms

    
    bucle++ ;
    value = bucle;
    
    String cuerpo = "site=" + agent + " &name=" + name + "&value=" + Irms;
    String lonPost = String(cuerpo.length());
    String post = ("POST / HTTP/1.1\r\nContent-Length:") + lonPost + "\r\n\r\n"+ cuerpo;
    
    
    Serial.println("\nStarting connection...");

    if (client.connect(IP_SERVER, PORT_SERVER)) 
      {
        Serial.println("connected");
        
        Serial.println(post); 
        client.println(post);
        
        client.println();
        
        delay(10000);
   
    }

  }
