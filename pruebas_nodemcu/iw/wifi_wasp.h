/*****************************/
/******** CONFIGURACION ******/
/*****************************/
#define SITE "Prueba"
#define LOGIN "casaelobrero"
#define PASSWORD "lacosamasbonitadelmundo"
#define IP_SERVER "192.168.1.139"
#define PORT_SERVER 7000

/*****************************/


// Function Prototypes

void wifi_connect();
void pandora_post(String);

// Function definitions
void wifi_connect()
  {
    WiFi.begin();
    delay(5000);
    WiFi.begin(LOGIN, PASSWORD);
    Serial.print("\ntry Connecting wifi");
    delay(5000);
    Serial.print("\nIP address: ");
    Serial.println(WiFi.localIP());   
  }

void pandora_post(String post)
  {
   if (client.connect(IP_SERVER, PORT_SERVER)) 
    {
      Serial.println("server connected");
      client.println(post);
    
      unsigned long timeout = millis();
      while (client.available() == 0) 
        {
          if (millis() - timeout > 5000) 
            {
              Serial.println(">>> Client Timeout !");
              client.stop();
              return;
            }
        }
      
      // Read all the lines of the reply from server and print them to Serial
      while(client.available())
        {
          String line = client.readStringUntil('\r');
          Serial.print("server response:");
          Serial.println(line);
        }  
    }
    
    else 
      {
        wifi_connect();
      }  
  }


