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


#include "wifi_client.h"

#include "temperature_sensor.h"

// Para la serialización de wifi
SoftwareSerial mySerial(3, 2); /* RX:D3, TX:D2 */
ESP8266S wifi_m(mySerial);


void setup(void)
{ 
    Serial.begin(115200);
    setupWifi(wifi_m);
    temperatureSensorsBegin();
}


void loop(void)
{
    buildTemperatureMessage(wifi_m);
    
}

