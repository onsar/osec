#include <OneWire.h>
#include <DallasTemperature.h>
#include "temperature_sensor_configuration.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
// DeviceAddress insideThermometer, outsideThermometer;
DeviceAddress tempDeviceAddress;

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

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  
  // locate devices on the bus
  
  Serial.println("Locating devices..."); 
  numberOfDevices = sensors.getDeviceCount();
  Serial.println("********************"); 
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");
  Serial.println("********************"); 
  

  
// *******************  Empieza el bucle


  // Loop through each device, print out address and configuration
  // reolution, alarms
  
  for(int i=0;i<numberOfDevices; i++)
  {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i))
    {
        Serial.print("Found device ");
        Serial.print(i, DEC);
        Serial.print(" with address: ");
        printAddress(tempDeviceAddress);
        Serial.println();
        
        Serial.print("Setting resolution to ");
        Serial.println(TEMPERATURE_PRECISION, DEC);
        
        // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
        sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
        
        Serial.print("Resolution actually set to: ");
        Serial.print(sensors.getResolution(tempDeviceAddress), DEC); 
        Serial.println();
        
        Serial.println("current alarm setup: ");   
        printAlarms(tempDeviceAddress);
        Serial.println();
        
        Serial.println("Setting alarm temp...");

        // alarm when temp is higher than 30C

        sensors.setHighAlarmTemp(tempDeviceAddress, HIGH_TEMPERATURE_ALARM);
    
        // alarm when temp is lower than -10C
        sensors.setLowAlarmTemp(tempDeviceAddress, LOW_TEMPERATURE_ALARM);
        
        Serial.println("NEW alarm temp...");   
        printAlarms(tempDeviceAddress);
        Serial.println();

        
    }
  
  else{
    Serial.print("Found ghost device at ");
    Serial.print(i, DEC);
    Serial.print(" but could not detect address. Check power and cabling");
  }
  }
  
}

/**************************************/
/*********  FUNCIONES *****************/
/**************************************/
  
/** Comparar direcciones ***/

bool compareAddress(DeviceAddress deviceAddress_c_1, DeviceAddress deviceAddress_c_2){
  for(int i=0;i<7; i++){
    if (deviceAddress_c_1[i] != deviceAddress_c_2[i]){return false;}
  }
  return true;
}

  
/** imprimir deviceAddress ***/

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


/** imprimir la temperatura de un sensor ***/ 

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

// function to print High and Low alarmas
void printAlarms(uint8_t deviceAddress[])
{
  char temp;
  temp = sensors.getHighAlarmTemp(deviceAddress);
  Serial.print("High Alarm: ");
  Serial.print(temp, DEC);
  Serial.print("C/");
  Serial.print(DallasTemperature::toFahrenheit(temp));
  Serial.print("F | Low Alarm: ");
  temp = sensors.getLowAlarmTemp(deviceAddress);
  Serial.print(temp, DEC);
  Serial.print("C/");
  Serial.print(DallasTemperature::toFahrenheit(temp));
  Serial.print("F");
}

/** Imprimir la informacion principal de un dispositivo ***/

void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  
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
  
  Serial.print(" ");
  printTemperature(deviceAddress);
  
}
// Imprime todos los datos incluidas las alarmas
void checkAlarm(DeviceAddress deviceAddress)
{
  printData(deviceAddress); 
  if (sensors.hasAlarm(deviceAddress))
    {
      Serial.print(" ALARM");
    }
  else 
    {
      Serial.print(" NO ALARM");
    }
  Serial.println();
}

void loop(void)
{ 
  // CALL sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");
   for(int i=0;i<numberOfDevices; i++)
   {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i))
    {
    checkAlarm(tempDeviceAddress);   
    Serial.println();
    }
   }

}

