#include <ESP8266WiFi.h>

WiFiClient client;

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
  
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    // srv:connect(7000,"192.168.1.136")
    if (client.connect("192.168.1.136", 7000)) 
      {
        Serial.println("connected");
        // ("POST / HTTP/1.1\r\nContent-Length:"..n.."\r\n\r\n  ".. post_data)
        client.println("POST /search?q=arduino HTTP/1.0");
        client.println();
      }
  }

void loop() {}
