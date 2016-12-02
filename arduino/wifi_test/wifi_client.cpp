
#include "ESP8266S.h"
//#include <string.h>
#include "wifi_configuration.h"
#include "wifi_client.h"




bool setupWifi(ESP8266S &wifi)
{ 
    Serial.print("setup wifi begin\r\n");

    Serial.print("FW Version: ");
    Serial.println(wifi.getVersion().c_str());


    
    if (wifi.setOprToStation()) {
        Serial.print("to station ok\r\n");
    } 
    else {
        Serial.print("to station err\r\n");        
    }
    
    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }
    
    
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");       
        Serial.println(wifi.getLocalIP().c_str());
    } else {
        Serial.print("Join AP failure\r\n");
    }


    if (wifi.disableMUX()) {Serial.print("single ok\r\n");} 
    else {Serial.print("single err\r\n");}
    
    Serial.print("setup end\r\n");
}





bool send_msj(String msj_string, ESP8266S &wifi)
//bool send_msj(String msj_string)
//bool send_msj(msj_string)

{
    
    uint8_t buffer[128] = {0};

    if (wifi.setOprToStation()) {
        Serial.print("to station ok\r\n");
    } 
    else {
        Serial.print("to station err\r\n");
    }
    
    if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
        Serial.print("create tcp ok\r\n");
    } 
    else {
        Serial.print("create tcp err\r\n");
    }

    const char *hello = msj_string.c_str();
    wifi.send((const uint8_t*)hello, strlen(hello));

     
    uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
    if (len > 0) {
        Serial.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
    }
    
    if (wifi.releaseTCP()) {
        Serial.print("release tcp ok\r\n");
    } else {
        Serial.print("release tcp err\r\n");
    }    
    
}


