

// definies
#include "pressure_sensor_configuration.h"

// variable declaration
int pinPressureSensor[PRESSURE_DEVICES_NUMBER];
int numberOfDevices; // Creo que sobra!!!!!!!!

// Function Prototypes
void pressureSensorMessage();
void printDataPressureSensor(int); 
void printPressure(int);
 
 

void setup() 
    {
        // initialize serial communication at 9600 bits per second:
        Serial.begin(9600);
        
        // pressures pin sensor matrix
        if (PRESSURE_DEVICES_NUMBER > 0) pinPressureSensor[0]=PRESSURE_INPUT_1;
        if (PRESSURE_DEVICES_NUMBER > 1) pinPressureSensor[1]=PRESSURE_INPUT_2;
        if (PRESSURE_DEVICES_NUMBER > 2) pinPressureSensor[2]=PRESSURE_INPUT_3;    
        if (PRESSURE_DEVICES_NUMBER > 3) pinPressureSensor[3]=PRESSURE_INPUT_4;    
        if (PRESSURE_DEVICES_NUMBER > 4) pinPressureSensor[4]=PRESSURE_INPUT_5;    
        if (PRESSURE_DEVICES_NUMBER > 5) pinPressureSensor[5]=PRESSURE_INPUT_6; 
        

        
        //maintenance message

        Serial.print("{\"maint_data_press_sensor\":{"); 

        // Search the wire for address
        if(PRESSURE_DEVICES_NUMBER)
            {
                pressureSensorMessage();
            }

        else
            {
                Serial.print("NO HAY DISPOSITIVOS CONFIGURADOS. ");
                Serial.print("Revisa el fichero de configuración:pressure_sensor_configuration.h");
            }

        // Close mintenence, message
        Serial.println("}}"); 
        
    }

void loop() 
    {
        pressureSensorMessage();
    }



void pressureSensorMessage()
    {
        // esta repetido en los otros mensajes
        uint32_t time = millis();
        
        // cabecera del mensaje
        Serial.print("{\"data_sensor\":{\"code\":\"50001\",\"number\":\"001\",\"name\":\"San Pablo\",\"time_0x\":\""); 
        Serial.print(time); 
        Serial.print("\",");
        
        // pressure message for each sensor
        Serial.print("\"pressure_sensors\":{");
        
        for(int i=0;i<PRESSURE_DEVICES_NUMBER; i++)
            {
                printDataPressureSensor(i); 
                if (i < (PRESSURE_DEVICES_NUMBER-1))Serial.print(",");
                
            }
            
        // close data_sensor,message    
        Serial.println("}}}");
    
    }
void printDataPressureSensor(int n) 
    {
        // presssure id
        Serial.print("\"sensor_");
        Serial.print(n);
        Serial.print("\":{");
        Serial.print("\"id\":\"");
        Serial.print(pinPressureSensor[n]);
        Serial.print("\","); 
    
        // presssure name
        Serial.print("\"name\":\"");
        if      (pinPressureSensor[n]== PRESSURE_INPUT_1)   {Serial.print(PRESSURE_SENSOR_NAME_1); }
        else if (pinPressureSensor[n]== PRESSURE_INPUT_2)   {Serial.print(PRESSURE_SENSOR_NAME_2); }
        else if (pinPressureSensor[n]== PRESSURE_INPUT_3)   {Serial.print(PRESSURE_SENSOR_NAME_3); }
        else if (pinPressureSensor[n]== PRESSURE_INPUT_4)   {Serial.print(PRESSURE_SENSOR_NAME_4); }            
        else if (pinPressureSensor[n]== PRESSURE_INPUT_5)   {Serial.print(PRESSURE_SENSOR_NAME_5); }            
        else if (pinPressureSensor[n]== PRESSURE_INPUT_6)   {Serial.print(PRESSURE_SENSOR_NAME_6); }            
        else {Serial.print( "Nombre no declarado"); }            
        Serial.print("\","); 
            
        // presssure data
        Serial.print("\"press\":\"");
        printPressure(pinPressureSensor[n]);
        Serial.print("\"");
        
        Serial.print("}"); // sensor close
    }


void printPressure(int pin)
    {
        uint32_t sensorValue = analogRead(pin);
        // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
        uint32_t voltage = sensorValue * (5000 / 1023);
        // print out the value you read:
        Serial.print(voltage); 
    }

  



