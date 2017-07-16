
#include <ESP8266WiFi.h>
WiFiClient client;
#include "wifi_wasp.h" 

String agent = SITE;

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance
const int AnalogIn = A0;
int readingIn = 0;
String name = "Intensidad";
int value = 0;

void setup()
  {
    Serial.begin(115200);
    Serial.println();

    emon1.current(A0,31.4);             // Current: input pin, calibration.
      
    wifi_connect();
  }


void loop() 
  {
    double Irms = emon1.calcIrms(4480);  // Calculate Irms only
    
    Serial.println("************");
    Serial.print("W:");
    Serial.print(Irms*230.0);         // Apparent power
    Serial.print(" - Irms:");
    Serial.println(Irms);             // Irms
    
    String cuerpo = "site=" + agent + " &name=" + name + "&value=" + Irms;
    String lonPost = String(cuerpo.length());
    String intensity_post = ("POST / HTTP/1.1\r\nContent-Length:") + lonPost + "\r\n\r\n"+ cuerpo;
    Serial.println(intensity_post); 
    pandora_post(intensity_post);
    
    delay(3000);
  }


  







  
