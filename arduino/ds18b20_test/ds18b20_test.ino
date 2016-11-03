#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

#define TEMPERATURE_PRECISION 9 // Lower resolution

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
// DeviceAddress insideThermometer, outsideThermometer;
DeviceAddress tempDeviceAddress;

int numberOfDevices; // Number of temperature devices found



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
    
    Serial.println("current alarm temp...");   
    printAlarms(tempDeviceAddress);
    Serial.println();
    
    Serial.println("Setting alarm temp...");

    // alarm when temp is higher than 30C
    sensors.setHighAlarmTemp(tempDeviceAddress, 30);
  
    // alarm when temp is lower than -10C
    sensors.setLowAlarmTemp(tempDeviceAddress, -10);
    
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

/*********  FUNCIONES **********/


// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// function to PRINT THE TEMPERATURE for a device 
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

// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
}
// function to check alarm
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

