#ifndef current_sensor_configuration_h
#define current_sensor_configuration_h


// *******************************************************
// *********** CONFIGURACION SENSORES ANALOGICOS *********
// *******************************************************


#define DEVICES_NUMBER 4

#define  SENSOR_NAME_1 "Intensidad total" // nombre del sensor
#define  INPUT_1  0 // pin de entrada analógica

// Factor de correccion = miliamperios maximos / milivoltios salida sensor 
// es un entero
// 100000/4000 = 25
#define  FACTOR_1 25;

#define  SENSOR_NAME_2 "Intensidad de salida modulo 1" 
#define  INPUT_2  1
#define  FACTOR_2 25;

#define  SENSOR_NAME_3 "Presion sistma principal" 
#define  INPUT_3  2
#define  FACTOR_3 1; //10.000 milibares 10.000 milivoltios

#define  SENSOR_NAME_4 "Presion deposito general" 
#define  INPUT_4  3
#define  FACTOR_4 1;


// *******************************************************



// variable declaration
int  matix_declaration =1;
uint32_t pinCurrentSensor[DEVICES_NUMBER][2];

// Function Prototypes
void analogicalSensorMessage();
void matrix_configuration();
String printDataCurrentSensor(int pin);


void analogicalSensorMessage()
    {
        Serial.println(F("Sensores de de medida analogica"));

        if(matix_declaration) matrix_configuration();
        
        for(int i=0;i<DEVICES_NUMBER; i++)
        
            {
                               
                Serial.print(F("numero device: "));
                Serial.print(i);

                int pin = pinCurrentSensor[i][0];
                Serial.print(F(" pin: "));
                Serial.print(pin);
                
                String sensor_name = printDataCurrentSensor(pin); 
                Serial.print(F("  sensor_name: "));
                Serial.print(sensor_name);
                

                uint32_t sensorValue = analogRead(pin);
                // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
                // uint32_t voltage = sensorValue * (5000 / 1023);

                float field_value = float(sensorValue * pinCurrentSensor[i][1]*5)/float(1023);
                String value_An = String(field_value,2);              
                
                Serial.print (F("  sensorValue: ")); 
                Serial.println (sensorValue); 
                
                Serial.print (F("field_value: ")); 
                Serial.println (field_value); 

                Serial.print (F("value_An: "));
                Serial.print (value_An);               

                wifiBasic.enviarPost(sensor_name, value_An);            
                
            }

    
    }

void matrix_configuration()
    {

        Serial.println (F("matrix_configuration"));
        
        if (DEVICES_NUMBER > 0) { pinCurrentSensor[0][0]=INPUT_1; pinCurrentSensor[0][1]= FACTOR_1; }
        
        if (DEVICES_NUMBER > 1) { pinCurrentSensor[1][0]=INPUT_2; pinCurrentSensor[1][1]= FACTOR_2; }

        if (DEVICES_NUMBER > 2) { pinCurrentSensor[2][0]=INPUT_3; pinCurrentSensor[2][1]= FACTOR_3; }

        if (DEVICES_NUMBER > 3) { pinCurrentSensor[3][0]=INPUT_4; pinCurrentSensor[3][1]= FACTOR_4; }
  
        matix_declaration = 0 ;
  
    }

    
String  printDataCurrentSensor(int pin) 
    {

        String r = "";

        // current sensor name
        if      (pin == INPUT_1)   { r= (SENSOR_NAME_1); }
        else if (pin == INPUT_2)   { r= (SENSOR_NAME_2); } 
        else if (pin == INPUT_3)   { r= (SENSOR_NAME_3); } 
        else if (pin == INPUT_4)   { r= (SENSOR_NAME_4); } 

              
        else {r=  "Nombre no declarado"; }            
        
        return r;
        
    }


  #endif

