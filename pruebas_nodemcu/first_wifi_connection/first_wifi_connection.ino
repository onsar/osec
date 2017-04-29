#include <ESP8266WiFi.h>

WiFiClient client;
String agent = "prueba";
String name = "contador";
int value = 0;
int bucle = 0;

void setup()
  {
    Serial.begin(115200);
    Serial.println();
  
    WiFi.begin("casaelobrero", "lacosamasbonitadelmundo");
    
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }
    Serial.println();
    
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
  

  }

void loop() 
  {
    bucle++ ;
    value = bucle;
    String cuerpo = "site=" + agent + " &name=" + name + "&value=" + value;
    String lonPost = String(cuerpo.length());
    String post = ("POST / HTTP/1.1\r\nContent-Length:") + lonPost + "\r\n\r\n"+ cuerpo;
    
    
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    // srv:connect(7000,"192.168.1.136")
    if (client.connect("192.168.1.137", 7000)) 
      {
        Serial.println("connected");
        
        Serial.println(post); 
        client.println(post);
        
        client.println();
        
        delay(1000);
   
    }

  }
