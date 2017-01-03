#ifndef temperature_sensor_h
#define temperature_sensor_h

#include <OneWire.h>
#include <DallasTemperature.h>
#include "temperature_sensor_configuration.h"
// #include "wifi_basic.h"

// void buildTemperatureMessage(ESP8266S &wifi_t);
void buildTemperatureMessage();
String printData(DeviceAddress deviceAddress);
bool compareAddress(DeviceAddress deviceAddress_c_1, DeviceAddress deviceAddress_c_2);
void printResoltion(DeviceAddress deviceAddressPr);
// void printAddress(DeviceAddress deviceAddressPa);
String printAddress(DeviceAddress deviceAddressPa);
void printTemperature(DeviceAddress deviceAddressPt);

void temperatureSensorsBegin();




DeviceAddress tempDeviceAddress;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors_m(&oneWire);


 //DeviceAddress
uint8_t deviceAddress_1[]=POSITION_1;
uint8_t deviceAddress_2[]=POSITION_2;
uint8_t deviceAddress_3[]=POSITION_3;
uint8_t deviceAddress_4[]=POSITION_4;
uint8_t deviceAddress_5[]=POSITION_5;
uint8_t deviceAddress_6[]=POSITION_6;
uint8_t deviceAddress_7[]=POSITION_7;
uint8_t deviceAddress_8[]=POSITION_8;
uint8_t deviceAddress_9[]=POSITION_9;
uint8_t deviceAddress_10[]=POSITION_10;
uint8_t deviceAddress_11[]=POSITION_11;
uint8_t deviceAddress_12[]=POSITION_12;

String temperatureString = (""); 
uint8_t numberOfDevices=0;


// void buildTemperatureMessage(ESP8266S &wifi_t) {   
// void temperatureSensorMessage(){

void buildTemperatureMessage() {

    numberOfDevices = sensors_m.getDeviceCount();
    Serial.println("*******************  numberOfDevices");
    Serial.println(numberOfDevices);
    sensors_m.requestTemperatures();

    
    
    for(int i=0;i<numberOfDevices; i++)
        {
               if(sensors_m.getAddress(tempDeviceAddress, i))
               Serial.println(i);
               float tempC = sensors_m.getTempC(tempDeviceAddress);
               String value_18 = String(tempC,1);
               // String name_18 = "San_Pablo-temperatura-entrada-panel" + String(i);
               String name_18 = printData(tempDeviceAddress);
               Serial.println(value_18);
               Serial.println(name_18);
               wifiBasic.enviarPost(name_18, value_18);
        }
}


String printData(DeviceAddress deviceAddress)
{
  
  String temp_sensor_name;

  
  // Incluye el nombre del sensor
  if(compareAddress(deviceAddress,deviceAddress_1)) {temp_sensor_name = (NAME_SENSOR_1);}
  else if(compareAddress(deviceAddress,deviceAddress_2))  {temp_sensor_name = (NAME_SENSOR_2);} 
  else if(compareAddress(deviceAddress,deviceAddress_3))  {temp_sensor_name = (NAME_SENSOR_3);} 
  else if(compareAddress(deviceAddress,deviceAddress_4))  {temp_sensor_name = (NAME_SENSOR_4);} 
  else if(compareAddress(deviceAddress,deviceAddress_5))  {temp_sensor_name = (NAME_SENSOR_5);}  
  else if(compareAddress(deviceAddress,deviceAddress_6))  {temp_sensor_name = (NAME_SENSOR_6);} 
  else if(compareAddress(deviceAddress,deviceAddress_7))  {temp_sensor_name = (NAME_SENSOR_7);}  
  else if(compareAddress(deviceAddress,deviceAddress_8))  {temp_sensor_name = (NAME_SENSOR_8);}  
  else if(compareAddress(deviceAddress,deviceAddress_9))  {temp_sensor_name = (NAME_SENSOR_9);} 
  else if(compareAddress(deviceAddress,deviceAddress_10)) {temp_sensor_name = (NAME_SENSOR_10);} 
  else if(compareAddress(deviceAddress,deviceAddress_11)) {temp_sensor_name = (NAME_SENSOR_11);} 
  else if(compareAddress(deviceAddress,deviceAddress_12)) {temp_sensor_name = (NAME_SENSOR_12);}   
  // else {temp_sensor_name = (" LOCALIZACION NO IDENTIFICADA"  ); }
  else temp_sensor_name = printAddress(deviceAddress);

  

/*
  temperatureString += ("\"temp_c\":\"");
  printTemperature(deviceAddress);
  temperatureString += ("\"");
  temperatureString += ("}"); // sensor close
 */

 return temp_sensor_name;
 
}

  
// Compare directions

bool compareAddress(DeviceAddress deviceAddress_c_1, DeviceAddress deviceAddress_c_2){
  for(int i=0;i<7; i++){
    if (deviceAddress_c_1[i] != deviceAddress_c_2[i]){return false;}
  }
  return true;
}


void printResoltion(DeviceAddress deviceAddressPr)
{
  temperatureString += (sensors_m.getResolution(deviceAddressPr), DEC); 
}


// Print deviceAddress

String printAddress(DeviceAddress deviceAddressPa)
{ 
  String string_temp_r="";
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddressPa[i] < 16) string_temp_r += ("0");
    uint8_t temp= (deviceAddressPa[i]);
    String stringTemp =  String(temp, HEX);  
    string_temp_r = string_temp_r +stringTemp;
  }
  return string_temp_r;
}


// Print tempearture

void printTemperature(DeviceAddress deviceAddressPt)
{
  float tempC = sensors_m.getTempC(deviceAddressPt);
  temperatureString += (tempC);
  Serial.println("printTemperature *************");
  Serial.println(temperatureString);
}


void temperatureSensorsBegin() {sensors_m.begin();}




#endif

