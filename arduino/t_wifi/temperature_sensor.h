#ifndef temperature_sensor_h
#define temperature_sensor_h

#include <OneWire.h>
#include <DallasTemperature.h>
#include "temperature_sensor_configuration.h"
#include "wifi_client.h"

void buildTemperatureMessage(ESP8266S &wifi_t);
void printData(DeviceAddress deviceAddress,int n, bool p_resolution);
bool compareAddress(DeviceAddress deviceAddress_c_1, DeviceAddress deviceAddress_c_2);
void printResoltion(DeviceAddress deviceAddressPr);
void printAddress(DeviceAddress deviceAddressPa);
void printTemperature(DeviceAddress deviceAddressPt);

void temperatureSensorsBegin();

#endif
