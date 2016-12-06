 

// #include "ESP8266S.h"
// #include <string.h>
// #include "wifi_client.h"

#include "temperature_sensor.h"

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)

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


void buildTemperatureMessage(ESP8266S &wifi_t) {   
// void temperatureSensorMessage(){


    numberOfDevices = sensors_m.getDeviceCount();
    sensors_m.requestTemperatures();

    connectTCPWifi(wifi_t);
    uint32_t time = millis();
    temperatureString == ("");
    temperatureString = ("{\"data_sensor\":{\"code\":\"50001\",\"number\":\"001\",\"name\":\"San Pablo\",\"time_0x\":\""); 
    temperatureString += (time); 
    temperatureString += ("\",");
    send_msj(temperatureString,wifi_t);
    temperatureString = (""); 
   

    temperatureString += ("\"temperature_sensors\":{");
    
    send_msj(temperatureString,wifi_t);
    temperatureString = (""); 
    
    
    for(int i=0;i<numberOfDevices; i++)
        {
            // Search the wire for address
            if(sensors_m.getAddress(tempDeviceAddress, i))
                {
                    printData(tempDeviceAddress,i,false); 
                    if (i < (numberOfDevices-1))
                    {
                          temperatureString += (",");
                          send_msj(temperatureString,wifi_t);
                          temperatureString = (""); 
                    }
                }
            
        }
    // close temperature_sensors,data_sensor,message    
    temperatureString += ("}}}");

    send_msj(temperatureString,wifi_t);
    temperatureString = (""); 
    releaseTCPWifi(wifi_t);
    
}


void printData(DeviceAddress deviceAddress,int n, bool p_resolution)
{
  temperatureString += ("\"sensor_");
  temperatureString += (n);
  temperatureString += ("\":{");
  
  temperatureString += ("\"id\":\"");
  printAddress(deviceAddress);
  temperatureString += ("\","); 
  
  temperatureString += ("\"name\":\"");
  
  // Incluye el nombre del sensor
  if(compareAddress(deviceAddress,deviceAddress_1)) {temperatureString += (NAME_SENSOR_1);}
  else if(compareAddress(deviceAddress,deviceAddress_2))  {temperatureString += (NAME_SENSOR_2);} 
  else if(compareAddress(deviceAddress,deviceAddress_3))  {temperatureString += (NAME_SENSOR_3);} 
  else if(compareAddress(deviceAddress,deviceAddress_4))  {temperatureString += (NAME_SENSOR_4);} 
  else if(compareAddress(deviceAddress,deviceAddress_5))  {temperatureString += (NAME_SENSOR_5);}  
  else if(compareAddress(deviceAddress,deviceAddress_6))  {temperatureString += (NAME_SENSOR_6);} 
  else if(compareAddress(deviceAddress,deviceAddress_7))  {temperatureString += (NAME_SENSOR_7);}  
  else if(compareAddress(deviceAddress,deviceAddress_8))  {temperatureString += (NAME_SENSOR_8);}  
  else if(compareAddress(deviceAddress,deviceAddress_9))  {temperatureString += (NAME_SENSOR_9);} 
  else if(compareAddress(deviceAddress,deviceAddress_10)) {temperatureString += (NAME_SENSOR_10);} 
  else if(compareAddress(deviceAddress,deviceAddress_11)) {temperatureString += (NAME_SENSOR_11);} 
  else if(compareAddress(deviceAddress,deviceAddress_12)) {temperatureString += (NAME_SENSOR_12);}   
  else {temperatureString += (" LOCALIZACION NO IDENTIFICADA"  ); }
  temperatureString += ("\","); 
  
  // Resolution data
  if(p_resolution)
    {
        temperatureString += ("\"res\":\"");
        printResoltion(deviceAddress);
        temperatureString += ("\","); 
    }
    
  // Temeperature data
  temperatureString += ("\"temp_c\":\"");
  printTemperature(deviceAddress);
  temperatureString += ("\"");
  temperatureString += ("}"); // sensor close
  
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

void printAddress(DeviceAddress deviceAddressPa)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddressPa[i] < 16) temperatureString += ("0");
    uint8_t temp= (deviceAddressPa[i]);
    String stringTemp =  String(temp, HEX);  
    temperatureString = temperatureString +stringTemp;
  }
}


// Print tempearture

void printTemperature(DeviceAddress deviceAddressPt)
{
  float tempC = sensors_m.getTempC(deviceAddressPt);
  temperatureString += (tempC);
}


void temperatureSensorsBegin() {sensors_m.begin();}



