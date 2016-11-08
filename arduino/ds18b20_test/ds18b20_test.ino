/*
 * 
 * v01 2016-11-08
 * Envio formato json
 * Borrado alamras temperatura
 * 
 */

#include <OneWire.h>
#include <DallasTemperature.h>
#include "temperature_sensor_configuration.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

DeviceAddress tempDeviceAddress;

// Number of temperature devices found
int numberOfDevices; // Number of temperature devices found

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

bool compareAddress(DeviceAddress deviceAddress_c_1, DeviceAddress deviceAddress_c_2);
void printAddress(DeviceAddress deviceAddress);

// Function Prototypes
void printTemperature(DeviceAddress deviceAddress);
void printResoltion(DeviceAddress deviceAddress);
void printData(DeviceAddress deviceAddress,int n, bool p_resolution);
void temperatureSensorMessage();

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // Start serial port
  Serial.begin(9600);
  Serial.print("{\"maint_search_temp_sensor\":{");

  // Start up the library
  sensors.begin();
  
  // Locate devices on the bus

  numberOfDevices = sensors.getDeviceCount();
  Serial.print("\"devices_found\":\"YES\",");
  Serial.print("\"num_devices:\":\"");
  Serial.print(numberOfDevices, DEC);
  Serial.print("\"");
  
  // Close mintenence, message
  Serial.println("}}");  


  // Loop through each device, print out address and configuration
  // Reolution alarms configuration
  Serial.print("{\"maint_data_temp_sensor\":{"); 
  for(int i=0;i<numberOfDevices; i++)
        // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
    {
        // Search the wire for address
        if(sensors.getAddress(tempDeviceAddress,i))
            {
                sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
                printData(tempDeviceAddress,i,true); 
                if (i < (numberOfDevices-1))Serial.print(",");
            }

        else
            {
                Serial.print("Found ghost device at ");
                Serial.print(i, DEC);
                Serial.print(" but could not detect address. Check power and cabling");
            }
            
    }  
        // Close mintenence, message
        Serial.println("}}"); 
}


/**************************************/
/*********   LOOP     *****************/
/**************************************/

void loop(void)
{ 
  temperatureSensorMessage();
}


/**************************************/
/*********  FUNCTIONS *****************/
/**************************************/
  
// Compare directions

bool compareAddress(DeviceAddress deviceAddress_c_1, DeviceAddress deviceAddress_c_2){
  for(int i=0;i<7; i++){
    if (deviceAddress_c_1[i] != deviceAddress_c_2[i]){return false;}
  }
  return true;
}

  
// Print deviceAddress

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


// Print tempearture

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print(tempC);
}

void printResoltion(DeviceAddress deviceAddress)
{
  Serial.print(sensors.getResolution(deviceAddress), DEC); 
}

//Main data print function
void printData(DeviceAddress deviceAddress,int n, bool p_resolution)
{
  Serial.print("\"sensor_");
  Serial.print(n);
  Serial.print("\":{");
  
  Serial.print("\"id\":\"");
  printAddress(deviceAddress);
  Serial.print("\","); 
  
  Serial.print("\"name\":\"");
  // Incluye el nombre del sensor
  if(compareAddress(deviceAddress,deviceAddress_1)) {Serial.print(NAME_SENSOR_1);}
  else if(compareAddress(deviceAddress,deviceAddress_2))  {Serial.print(NAME_SENSOR_2);} 
  else if(compareAddress(deviceAddress,deviceAddress_3))  {Serial.print(NAME_SENSOR_3);} 
  else if(compareAddress(deviceAddress,deviceAddress_4))  {Serial.print(NAME_SENSOR_4);} 
  else if(compareAddress(deviceAddress,deviceAddress_5))  {Serial.print(NAME_SENSOR_5);}  
  else if(compareAddress(deviceAddress,deviceAddress_6))  {Serial.print(NAME_SENSOR_6);} 
  else if(compareAddress(deviceAddress,deviceAddress_7))  {Serial.print(NAME_SENSOR_7);}  
  else if(compareAddress(deviceAddress,deviceAddress_8))  {Serial.print(NAME_SENSOR_8);}  
  else if(compareAddress(deviceAddress,deviceAddress_9))  {Serial.print(NAME_SENSOR_9);} 
  else if(compareAddress(deviceAddress,deviceAddress_10)) {Serial.print(NAME_SENSOR_10);} 
  else if(compareAddress(deviceAddress,deviceAddress_11)) {Serial.print(NAME_SENSOR_11);} 
  else if(compareAddress(deviceAddress,deviceAddress_12)) {Serial.print(NAME_SENSOR_12);}   
  else {Serial.print(" LOCALIZACION NO IDENTIFICADA"  ); }
  Serial.print("\","); 
  
  // Resolution data
  if(p_resolution)
    {
        Serial.print("\"res\":\"");
        printResoltion(deviceAddress);
        Serial.print("\","); 
    }
    
  // Temeperature data
  Serial.print("\"temp_c\":\"");
  printTemperature(deviceAddress);
  Serial.print("\"");
  Serial.print("}"); // sensor close
  
}


void temperatureSensorMessage(){
    uint32_t time = millis();
 //   Serial.print("{\"data_sensor\":{\"code\":\"50001\",\"number\":\"001\",\"name\":\"San Pablo\",\"time_0x\":\"12345678\",\"temperature_sensors\":{");    
    Serial.print("{\"data_sensor\":{\"code\":\"50001\",\"number\":\"001\",\"name\":\"San Pablo\",\"time_0x\":\""); 
    Serial.print(time); 
    Serial.print("\",");
    
    // temperature sensor message

    Serial.print("\"temperature_sensors\":{");
 
    sensors.requestTemperatures();
    for(int i=0;i<numberOfDevices; i++)
        {
            // Search the wire for address
            if(sensors.getAddress(tempDeviceAddress, i))
                {
                    printData(tempDeviceAddress,i,false); 
                    if (i < (numberOfDevices-1))Serial.print(",");
                }
            
        }
     // close temperature_sensors,data_sensor,message    
    Serial.println("}}}");
    
}
