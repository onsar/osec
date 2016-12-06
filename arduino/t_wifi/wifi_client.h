


#ifndef wifi_client_h
#define wifi_client_h

// Para la serialización de wifi
#include "ESP8266S.h"
#include "wifi_configuration.h"


bool send_msj(String msj_string, ESP8266S &wifi);
bool setupWifi(ESP8266S &wifi);
bool connectTCPWifi(ESP8266S &wifi);
bool releaseTCPWifi(ESP8266S &wifi);


#endif
