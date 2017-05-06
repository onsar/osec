#ifndef temperature_sensor_h
#define temperature_sensor_h


// *******************************************************
// ******** CONFIGURACION SENSORES DE TEMPERATURA ********
// *******************************************************

// #define ONE_WIRE_BUS 6 // arduino uno
#define ONE_WIRE_BUS 4 // arduino nano

// Lower resolution
#define TEMPERATURE_PRECISION 9

//#define POSITION_1  {0x28,0xFF,0xFD,0x36,0x84,0x16,0x04,0x98}
#define POSITION_1  {0x28,0xA3,0x77,0x02,0x08,0x00,0x00,0x05}
#define NAME_SENSOR_1 "Temp_Out" 
#define POSITION_2  {0x28,0x7B,0x6B,0x02,0x08,0x00,0x00,0x3D}
#define NAME_SENSOR_2 "Temp_In" 
#define POSITION_3  {0x28,0x53,0x8E,0x01,0x08,0x00,0x00,0xAA}
#define NAME_SENSOR_3 "Temp_Amb"
#define POSITION_4  {0x28,0xFF,0x86,0x40,0x70,0x16,0x05,0x69}
#define NAME_SENSOR_4 "Tra Planta 3" 
#define POSITION_5  {0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE}
#define NAME_SENSOR_5 " SENSOR POSITION" 
#define POSITION_6  {0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE}
#define NAME_SENSOR_6 " SENSOR POSITIONL" 
#define POSITION_7  {0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE}
#define NAME_SENSOR_7 " SENSOR POSITION" 
#define POSITION_8  {0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE}
#define NAME_SENSOR_8 " SENSOR POSITION" 
#define POSITION_9  {0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE}
#define NAME_SENSOR_9 " SENSOR POSITION"
#define POSITION_10  {0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE}
#define NAME_SENSOR_10 " SENSOR POSITION"
#define POSITION_11  {0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE}
#define NAME_SENSOR_11 " SENSOR POSITION" 
#define POSITION_12  {0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE}
#define NAME_SENSOR_12 " SENSOR POSITION" 


// *******************************************************

#include <OneWire.h>
#include <DallasTemperature.h>

void buildTemperatureMessage(uint8_t);
String printName(DeviceAddress deviceAddress);
bool compareAddress(DeviceAddress deviceAddress_c_1, DeviceAddress deviceAddress_c_2);
void printResoltion(DeviceAddress deviceAddressPr);
String printAddress(DeviceAddress deviceAddressPa);
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



void buildTemperatureMessage(uint8_t output) {
  
    Serial.println(F("********buildTemperatureMessage()"));
    numberOfDevices = sensors_m.getDeviceCount();
    Serial.print(F("numberOfDevices = "));
    Serial.println(numberOfDevices);
    sensors_m.requestTemperatures();

    
    
    for(int i=0;i<numberOfDevices; i++)
        {
           if(sensors_m.getAddress(tempDeviceAddress, i))
           {
             Serial.print(F("****device number= "));
             Serial.println(i);
             float tempC = sensors_m.getTempC(tempDeviceAddress);
             String value_18 = String(tempC,1);
             String name_18 = printName(tempDeviceAddress);
             Serial.println(name_18 + ": " + value_18);             

             if (output==0) 
                 {
                      lcd.clear();
                      lcd.setCursor(0, 0); lcd.print(name_18);
                      lcd.setCursor(0, 1);lcd.print(value_18);
                      wifiBasic.enviarPost(name_18, value_18);
                                          
                  }


             if (output==1) 
                 {  
                     lcd.clear();
                     lcd.setCursor(0, 0); lcd.print(name_18);
                     lcd.setCursor(0, 1);lcd.print(value_18);
                     delay(4000);
                  }

             if (output==2) wifiBasic.enviarPost(name_18, value_18);
             

             
           }
        }
}


String printName(DeviceAddress deviceAddress)
{
  
  String temp_sensor_name;

  // Incluye el nombre del sensor
  if     (compareAddress(deviceAddress,deviceAddress_1))  {temp_sensor_name = F((NAME_SENSOR_1));}
  else if(compareAddress(deviceAddress,deviceAddress_2))  {temp_sensor_name = F((NAME_SENSOR_2));} 
  else if(compareAddress(deviceAddress,deviceAddress_3))  {temp_sensor_name = F((NAME_SENSOR_3));} 
  else if(compareAddress(deviceAddress,deviceAddress_4))  {temp_sensor_name = F((NAME_SENSOR_4));} 
  else if(compareAddress(deviceAddress,deviceAddress_5))  {temp_sensor_name = F((NAME_SENSOR_5));}  
  else if(compareAddress(deviceAddress,deviceAddress_6))  {temp_sensor_name = F((NAME_SENSOR_6));} 
  else if(compareAddress(deviceAddress,deviceAddress_7))  {temp_sensor_name = F((NAME_SENSOR_7));}  
  else if(compareAddress(deviceAddress,deviceAddress_8))  {temp_sensor_name = F((NAME_SENSOR_8));}  
  else if(compareAddress(deviceAddress,deviceAddress_9))  {temp_sensor_name = F((NAME_SENSOR_9));} 
  else if(compareAddress(deviceAddress,deviceAddress_10)) {temp_sensor_name = F((NAME_SENSOR_10));} 
  else if(compareAddress(deviceAddress,deviceAddress_11)) {temp_sensor_name = F((NAME_SENSOR_11));} 
  else if(compareAddress(deviceAddress,deviceAddress_12)) {temp_sensor_name = F((NAME_SENSOR_12));}   

  else temp_sensor_name = printAddress(deviceAddress);

 return temp_sensor_name;
 
}

  

bool compareAddress(DeviceAddress deviceAddress_c_1, DeviceAddress deviceAddress_c_2)
  {
    for(int i=0;i<7; i++)
      {
        if (deviceAddress_c_1[i] != deviceAddress_c_2[i]){return false;}
      }
    return true;
  }

void printResoltion(DeviceAddress deviceAddressPr)
{
  temperatureString += (sensors_m.getResolution(deviceAddressPr), DEC); 
}



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

void temperatureSensorsBegin() {sensors_m.begin();}



#endif

