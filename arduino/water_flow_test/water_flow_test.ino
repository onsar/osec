
// includes
#include "flow_sensor_configuration.h"

// variable declaration
int pinFlowSensor[FLOW_DEVICES_NUMBER];
volatile int NumEdges; //measuring the rising edges of the signal
int liters_hour;  

// Function Prototypes
void flowSensorMessage();
void printDataFlowSensor(int); 
void printFlow(int);
void edges_period();


// The setup() method runs once, when the sketch starts
void setup() //
    { 
        // initialize serial communication at 9600 bits per second:
        Serial.begin(9600);
        
        // pressures pin sensor matrix
        if (FLOW_DEVICES_NUMBER > 0) 
            {
                pinFlowSensor[0]=FLOW_INPUT_1;
                pinMode(FLOW_INPUT_1, INPUT);
            }
                    
        if (FLOW_DEVICES_NUMBER > 1)
            {
                pinFlowSensor[1]=FLOW_INPUT_2;
                pinMode(FLOW_INPUT_2, INPUT);
            }       
        
         
         //maintenance message 

         Serial.print("{\"maint_data_flow_sensor\":{"); 

        // Search the wire for address
        if(FLOW_DEVICES_NUMBER)
            {
                flowSensorMessage();
            }
            
        else
            {
                Serial.print("NO HAY DISPOSITIVOS CONFIGURADOS. ");
                Serial.print("Revisa el fichero de configuración:pressure_sensor_configuration.h");
            }

        // Close mintenence, message
        Serial.println("}}");         
    } 
    
void loop ()  
    {
        flowSensorMessage();
    }

    
void flowSensorMessage()
    {
        // esta repetido en los otros mensajes
        uint32_t time = millis();
        
        // cabecera del mensaje
        Serial.print("{\"data_sensor\":{\"code\":\"50001\",\"number\":\"001\",\"name\":\"San Pablo\",\"time_0x\":\""); 
        Serial.print(time); 
        Serial.print("\",");
        
        // pressure message for each sensor
        Serial.print("\"flow_sensors\":{");
        
        for(int i=0;i<FLOW_DEVICES_NUMBER; i++)
            {
                printDataFlowSensor(i); 
                if (i < (FLOW_DEVICES_NUMBER - 1))Serial.print(",");
                
            }
            
        // close data_sensor,message    
        Serial.println("}}}");
    } 
       
void printDataFlowSensor(int n) 
    {
        // presssure id
        Serial.print("\"sensor_");
        Serial.print(n);
        Serial.print("\":{");
        Serial.print("\"id\":\"");
        Serial.print(pinFlowSensor[n]);
        Serial.print("\","); 
    
        // flow name
        Serial.print("\"name\":\"");
        if      (pinFlowSensor[n]== FLOW_INPUT_1)   {Serial.print(FLOW_SENSOR_NAME_1); }
        else if (pinFlowSensor[n]== FLOW_INPUT_2)   {Serial.print(FLOW_SENSOR_NAME_2); }            
        else {Serial.print( "Nombre no declarado"); }            
        Serial.print("\","); 
            
        // presssure data
        Serial.print("\"l_hore\":\"");
        printFlow(pinFlowSensor[n]);
        Serial.print("\"");
        
        Serial.print("}"); // sensor close
    }

void printFlow(int pinF)
    {  
        NumEdges = 0; //Set NbTops to 0 ready for calculations
        attachInterrupt(digitalPinToInterrupt(pinF), edges_period, RISING);
        delay (1000);
        detachInterrupt(digitalPinToInterrupt(pinF)); 
        liters_hour = (NumEdges * 60 / (7.5));
        Serial.print (liters_hour, DEC);
    }
    
void edges_period() //This is the function that the interupt calls 
    { 
        NumEdges++; //This function measures the rising and falling edge of the hall effect sensors signal
    } 
    

