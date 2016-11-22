

// definies
#include "current_sensor_configuration.h"

// variable declaration
int pinCurrentSensor[CURRENT_DEVICES_NUMBER];

// Function Prototypes
void currentSensorMessage();
void printDataCurrentSensor(int); 
void printCurrent(int);
 
 

void setup() 
    {
        // initialize serial communication at 9600 bits per second:
        Serial.begin(9600);
        
        // current pins sensor matrix
        if (CURRENT_DEVICES_NUMBER > 0) pinCurrentSensor[0]=CURRENT_INPUT_1;
        if (CURRENT_DEVICES_NUMBER > 1) pinCurrentSensor[1]=CURRENT_INPUT_2;
        if (CURRENT_DEVICES_NUMBER > 2) pinCurrentSensor[2]=CURRENT_INPUT_3;    
        if (CURRENT_DEVICES_NUMBER > 3) pinCurrentSensor[3]=CURRENT_INPUT_4;    
        if (CURRENT_DEVICES_NUMBER > 4) pinCurrentSensor[4]=CURRENT_INPUT_5;    
        if (CURRENT_DEVICES_NUMBER > 5) pinCurrentSensor[5]=CURRENT_INPUT_6; 
        

        
        //maintenance message

        Serial.print("{\"maint_data_curr_sensor\":{"); 

        // Search the wire for address
        if(CURRENT_DEVICES_NUMBER)
            {
                currentSensorMessage();
            }

        else
            {
                Serial.print("NO HAY DISPOSITIVOS CONFIGURADOS. ");
                Serial.print("Revisa el fichero de configuración:current_sensor_configuration.h");
            }

        // Close mintenence, message
        Serial.println("}}"); 
        
    }

void loop() 
    {
        currentSensorMessage();
    }



void currentSensorMessage()
    {
        // esta repetido en los otros mensajes
        uint32_t time = millis();
        
        // cabecera del mensaje
        Serial.print("{\"data_sensor\":{\"code\":\"50001\",\"number\":\"001\",\"name\":\"San Pablo\",\"time_0x\":\""); 
        Serial.print(time); 
        Serial.print("\",");
        
        // current message for each sensor
        Serial.print("\"current_sensors\":{");
        
        for(int i=0;i<CURRENT_DEVICES_NUMBER; i++)
            {
                printDataCurrentSensor(i); 
                if (i < (CURRENT_DEVICES_NUMBER-1))Serial.print(",");
                
            }
            
        // close data_sensor,message    
        Serial.println("}}}");
    
    }
void printDataCurrentSensor(int n) 
    {
        // current id
        Serial.print("\"sensor_");
        Serial.print(n);
        Serial.print("\":{");
        Serial.print("\"id\":\"");
        Serial.print(pinCurrentSensor[n]);
        Serial.print("\","); 
    
        // current sensor name
        Serial.print("\"name\":\"");
        if      (pinCurrentSensor[n]== CURRENT_INPUT_1)   {Serial.print(CURRENT_SENSOR_NAME_1); }
        else if (pinCurrentSensor[n]== CURRENT_INPUT_2)   {Serial.print(CURRENT_SENSOR_NAME_2); }
        else if (pinCurrentSensor[n]== CURRENT_INPUT_3)   {Serial.print(CURRENT_SENSOR_NAME_3); }
        else if (pinCurrentSensor[n]== CURRENT_INPUT_4)   {Serial.print(CURRENT_SENSOR_NAME_4); }            
        else if (pinCurrentSensor[n]== CURRENT_INPUT_5)   {Serial.print(CURRENT_SENSOR_NAME_5); }            
        else if (pinCurrentSensor[n]== CURRENT_INPUT_6)   {Serial.print(CURRENT_SENSOR_NAME_6); }            
        else {Serial.print( "Nombre no declarado"); }            
        Serial.print("\","); 
            
        // current data
        Serial.print("\"curr\":\"");
        printCurrent(pinCurrentSensor[n]);
        Serial.print("\"");
        
        Serial.print("}"); // sensor close
    }


void printCurrent(int pin)
    {
        uint32_t sensorValue = analogRead(pin);
        // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
        uint32_t voltage = sensorValue * (5000 / 1023);
        // print out the value you read:
        Serial.print(voltage); 
    }

  



