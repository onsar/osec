 
#ifndef wifi_x_esp_h
#define wifi_x_esp_h


// ************************************
// ******** CONFIGURACION WIFI ********
// ************************************

# define LOCALIZACION "prueba"
# define SSID "casaelobrero"
# define PASS "lacosamasbonitadelmundo"

// *******************************************************

String agent = LOCALIZACION;

void wifi_conection()
  {
  
    if(WiFi.status() != WL_CONNECTED)
      {
        
        WiFi.begin(SSID, PASS);
        Serial.print("Connecting");
          while (WiFi.status() != WL_CONNECTED)
            {
              delay(500);
              Serial.print(".");
            }
      }
    else Serial.println("wifi ya conectada"); 
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

  }


WiFiClient client;

void enviarPost(String name, String value) 

  {
  
    String cuerpo = "site=" + agent + " &name=" + name + "&value=" + value;
    String lonPost = String(cuerpo.length());
    String post = ("POST / HTTP/1.1\r\nContent-Length:") + lonPost + "\r\n\r\n"+ cuerpo;

    wifi_conection();

     Serial.println("\nIniciando la conexion con el servidor...");
    // if you get a connection, report back via serial:
    // srv:connect(7000,"192.168.1.136")
    if (client.connect("192.168.1.137", 7000)) 
      {
        Serial.println("connected");
        
        Serial.println(post); 
        client.println(post);
        
        client.println();
        
        delay(10000);
      }
  
  }



























































#endif
