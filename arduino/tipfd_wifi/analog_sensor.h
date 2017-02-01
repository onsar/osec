
#ifndef current_sensor_configuration_h
#define current_sensor_configuration_h


// *******************************************************
// *********** CONFIGURACION SENSORES ANALOGICOS *********
// *******************************************************


#define DEVICES_NUMBER 3


// Factor de correccion = miliamperios maximos / milivoltios salida sensor 
// es un entero
// 100000/4000 = 25

#define  SENSOR_NAME_1 "Intensidad total" // nombre del sensor
#define  INPUT_1  0 // pin de entrada analógica
#define  FACTOR_1 25;

#define  SENSOR_NAME_2 "Presion sistma principal" 
#define  INPUT_2  1
#define  FACTOR_2 1; //10.000 milibares 10.000 milivoltios

// Factor de correccion = mili_segundos medida / mili_litros pulso
// es un entero
// 36.000.000/10.000 = 3600

#define  SENSOR_NAME_3 "caudal agua caliente" 
#define  INPUT_3  102
#define  FACTOR_3 3600;


/*
#define  SENSOR_NAME_4 "Intensidad de salida modulo 1" 
#define  INPUT_4  2
#define  FACTOR_4 25;

#define  SENSOR_NAME_5 "Presion deposito general" 
#define  INPUT_5  3
#define  FACTOR_5 1;

*/




// *******************************************************



// variable declaration
int  matix_declaration =1;
uint32_t pinCurrentSensor[DEVICES_NUMBER][2];
uint32_t time_last=1000;
uint32_t time_dif;

// Function Prototypes
void analogicalSensorMessage(uint8_t);
void matrix_configuration();
float analogValue (int pin_a);
String printDataCurrentSensor(int pin);

float interruptionRead(int pin);
void edges_period();


void analogicalSensorMessage(uint8_t output)
    {
        Serial.println(F("Sensores de de medida analogica"));
        // borrar, solo para pruebas
        // edges_period();

        if(matix_declaration) matrix_configuration();
        
        for(int i=0;i<DEVICES_NUMBER; i++)
        
            {
                // uint32_t sensorValue;  
                float field_value;    // valor de la medida         
                
                Serial.print(F("numero device: "));
                Serial.print(i);

                int pin = pinCurrentSensor[i][0];
                Serial.print(F(" pin: "));
                Serial.print(pin);
                
                String sensor_name = printDataCurrentSensor(pin); 
                Serial.print(F("  sensor_name: "));
                Serial.print(sensor_name);
                
                // numeracion de pines analogicos de 0 a 100                               
                if(pinCurrentSensor[i][0] < 100) field_value = analogValue(i);
                
                // numeración de interrupciones de 100 a 199
                if(pinCurrentSensor[i][0] > 99 && pinCurrentSensor[i][0] < 200 ) field_value = interruptionRead(i); 
                
                String value_An = String(field_value,2);

                Serial.print (F("output: ")); 
                Serial.println (output); 
                
                Serial.print (F("field_value: ")); 
                Serial.println (field_value); 

                Serial.print (F("value_An: "));
                Serial.println (value_An);  
                
                if (output==0||output==1) {  lcd.setCursor(0, 0); lcd.print(field_value);
                                             lcd.setCursor(0, 1); lcd.print(value_An);}
                if (output==0||output==2) wifiBasic.enviarPost(sensor_name, value_An);            
                
            }

    
    }

void matrix_configuration()
    {

        
        Serial.println (F("matrix_configuration"));
        
        if (DEVICES_NUMBER > 0) { pinCurrentSensor[0][0]=INPUT_1; pinCurrentSensor[0][1]= FACTOR_1; }
        
        if (DEVICES_NUMBER > 1) { pinCurrentSensor[1][0]=INPUT_2; pinCurrentSensor[1][1]= FACTOR_2; }

        if (DEVICES_NUMBER > 2) { pinCurrentSensor[2][0]=INPUT_3; pinCurrentSensor[2][1]= FACTOR_3; }

        // if (DEVICES_NUMBER > 3) { pinCurrentSensor[3][0]=INPUT_4; pinCurrentSensor[3][1]= FACTOR_4; }

        // if (DEVICES_NUMBER > 4) { pinCurrentSensor[4][0]=INPUT_5; pinCurrentSensor[4][1]= FACTOR_5; }

        attachInterrupt(digitalPinToInterrupt(pinCurrentSensor[4][0]-100), edges_period, RISING);
  
        matix_declaration = 0 ;
  
    }

float analogValue(int m_i)
    {
        uint32_t sensorValue_a = analogRead(pinCurrentSensor[m_i][0]); 
        float field_value_a = float(sensorValue_a * pinCurrentSensor[m_i][1]*5)/float(1023);
        Serial.print (F("  field_value_a: ")); 
        Serial.println (field_value_a); 
        return field_value_a;
    }

float interruptionRead(int m_i)
    {
        // caudal maximo 3000 litros/hora -> 50 litros/min -> pulsos  -> 5pulsos/min  -> 12 segundos entre pulso
        // caudal minimo 1 min pulso -> 10 litros minuto -> 600 litros/hora
        // 30 min sin pulsos -> menos de 0,33 litros/min indicamos 0l/hora ()
        
        
        float field_value_i =33.33;

        Serial.println(F(""));
        Serial.println(F("interruptionRead **************"));
        
        Serial.print(F("time_last: "));
        Serial.println(time_last);
        
        uint32_t time_0 = millis();

        if (time_last == 1000)
          {
              field_value_i = 0;
              Serial.println(F("if time_last = 1000"));
          }
          
        else if ((time_0 - time_last) > 1800000) 
          {
              field_value_i = 0;
              Serial.println(F("if time_0 - time_last > 1800000"));
          }


        else if (time_dif < time_0 -time_last) 
          {
              field_value_i = float((pinCurrentSensor[m_i][1]*10000)/(time_0 -time_last));
              Serial.println(F("if time_dif < time_0 - time_last"));
              
          }
          
        else field_value_i = float((pinCurrentSensor[m_i][1]*10000)/time_dif);
        
  
        Serial.print(F("time_dif: "));  
        Serial.println(time_dif);
        
        Serial.print (F("field_value_a: ")); 
        Serial.println (field_value_i);     

        
        return field_value_i;
    }

void edges_period() //This is the function that the interupt calls 
    { 
        uint32_t time_interruption = millis();
        if (time_interruption -time_last > 3000) 
          {
              time_dif = time_interruption -time_last;
              time_last=time_interruption; 
          }

        Serial.print(F("edges_period - time_last; "));  
        Serial.println(time_last);       
    } 
    
   
String  printDataCurrentSensor(int pin) 
    {

        String r = "";

        // current sensor name
        if      (pin == INPUT_1)   { r= (SENSOR_NAME_1); }
        else if (pin == INPUT_2)   { r= (SENSOR_NAME_2); } 
        else if (pin == INPUT_3)   { r= (SENSOR_NAME_3); } 
        // else if (pin == INPUT_4)   { r= (SENSOR_NAME_4); } 
        // else if (pin == INPUT_5)   { r= (SENSOR_NAME_5); } 

              
        else {r=  "Nombre no declarado"; }            
        
        return r;
        
    }


  #endif

