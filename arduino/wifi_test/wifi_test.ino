/**
 * @example ConnectarWiFi.ino
 * @brief The ConnectWiFi demo of library WeeESP8266. 
 * @author Oscar Puyal > 
 * @date 2016.12
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version. \n\n
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "ESP8266S.h"
#include <string.h>

// #define SSID "DELABS" //Nombre de la Red Wifi a la que nos conectamos
// #define PASSWORD "dellmacmolaano" //Contraseña de la Red Wifi
// #define HOST_NAME "192.168.1.136" // thingspeak.com

#define SSID "casaelobrero" //Nombre de la Red Wifi a la que nos conectamos
#define PASSWORD "lacosamasbonitadelmundo" //Contraseña de la Red Wifi
#define HOST_NAME "192.168.1.128" // thingspeak.com

#define HOST_PORT 7000

SoftwareSerial mySerial(3, 2); /* RX:D3, TX:D2 */
ESP8266S wifi(mySerial);

int msj_n;

bool send_msj(String msj_string);

void setup(void)
{ 
    Serial.begin(9600);
    Serial.print("setup begin\r\n");
    msj_n=0;

    Serial.print("FW Version: ");
    Serial.println(wifi.getVersion().c_str());


    
    if (wifi.setOprToStation()) {
        Serial.print("to station ok\r\n");
    } 
    else {
        Serial.print("to station err\r\n");        
    }
    
    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }
    
    
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");       
        Serial.println(wifi.getLocalIP().c_str());
    } else {
        Serial.print("Join AP failure\r\n");
    }


    if (wifi.disableMUX()) {Serial.print("single ok\r\n");} 
    else {Serial.print("single err\r\n");}
    
    Serial.print("setup end\r\n");
}

void loop(void)
{
    String str = "string yo tenia un caballo que nunca tropezaba, tendremos que probar con cadenas mas largas 444  -> ";
    str+= msj_n;

    send_msj(str);

    delay(3000);

}

bool send_msj(String msj_string)
//bool send_msj(msj_string)

{
    msj_n=msj_n+1;
    
    uint8_t buffer[128] = {0};

    if (wifi.setOprToStation()) {
        Serial.print("to station ok\r\n");
    } 
    else {
        Serial.print("to station err\r\n");
    }
    
    if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
        Serial.print("create tcp ok\r\n");
    } 
    else {
        Serial.print("create tcp err\r\n");
    }

    const char *hello = msj_string.c_str();
    wifi.send((const uint8_t*)hello, strlen(hello));

     
    uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
    if (len > 0) {
        Serial.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
    }
    
    if (wifi.releaseTCP()) {
        Serial.print("release tcp ok\r\n");
    } else {
        Serial.print("release tcp err\r\n");
    }    
    
}

