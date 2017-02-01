





#define SSID "casaelobrero"
#define PASS "lacosamasbonitadelmundo"

String ssid = SSID;
String pass = PASS;

String cwjap = "AT+CWJAP=\"" +  ssid +"\",\"" + pass + "\""  ;




String ordenesAT[]=
{
  "AT+CWMODE=1",//modo cliente de red
  // "AT+CWJAP=\"DELABS\",\"dellmacmolaano\"",
  // "AT+CWJAP=\"casaelobrero\",\"lacosamasbonitadelmundo\"",
  cwjap,
  "AT+CIPMUX=0",//Simple conexión 
  "AT+CIFSR",//ip asignada 
  "END"
};

String ordenClose[]=
{
  "AT+CIPCLOSE=0",
  "END"
};


String ordenConexion[]=
{
  // "AT+CIPSTART=\"TCP\",\"192.168.2.221\",9090",
  // "AT+CIPSTART=\"TCP\",\"192.168.1.128\",9090",
  "AT+CIPSTART=\"TCP\",\"193.146.117.35\",7000",
  "END"
};

// ******************************
// ********** clases ************
// ******************************

class WifiBasic {
  private:
  uint8_t wifi_conected;
  SoftwareSerial * wifiSerial;
  
  public:
  WifiBasic(SoftwareSerial* _wifiSerial);
  bool enviarPost(String name, String value);
  
  private:
  bool orden(String comando);
  bool respuesta();
  bool configurarWifi(String *ordenes);
};

// *****************************************
// ******* deficnicion de funciones  *******
// ****************************************

WifiBasic::WifiBasic(SoftwareSerial* _wifiSerial)
{
  wifiSerial= _wifiSerial;
  wifi_conected = 1; //wifi no conectada
  wifiSerial->begin(BPS);
  
}


bool WifiBasic::enviarPost(String name, String value)
{
  // void fpost( String output)
  // entrara nombre y valor
  lcd.setCursor(0, 0);
  lcd.print(name);
  lcd.setCursor(0, 1);
  lcd.print(value);
  
  uint8_t resultado;

  orden("AT+CWJAP?");
  
  if (wifiSerial->find("ERROR")) 
    {
      Serial.println("encontroado ERROR en CWJAP");
      wifi_conected = 1;
    }

  Serial.print(F("algoritmo: wifi_conected= "));
  Serial.println(wifi_conected);

  orden("AT+CWJAP?");
  respuesta();

  if(wifi_conected != 0)
  {
      wifi_conected = 0;
      configurarWifi(ordenesAT);  
  }

  configurarWifi(ordenConexion);
  delay(1000);

  String cuerpo = "name=" + name + "&value=" + value;
  String lonPost = String(cuerpo.length());
  // Serial.println (F("cuerpo_parte_1"));
  // Serial.println (cuerpo); 
  // Serial.println (lonPost);
  
 
  String post = "POST / HTTP/1.1\r\nContent-Length:" + lonPost + "\r\n\r\n"+ cuerpo;

  Serial.println (F("post ****"));
  Serial.println (post);
  
  // envia el post
  String comando= F("AT+CIPSEND=");
  Serial.println(comando+post.length());

  // envar comando al modulo wifi
  wifiSerial->print(comando.c_str());
  wifiSerial->println(post.length());
  

  delay(1000);
  if (wifiSerial->find(">"))
  
  {
    Serial.println(F("-- > --"));
    wifiSerial-> write(post.c_str());
    wifiSerial-> write ("\r\n");
    delay(3000);
    int resultado = respuesta();
    delay(100);
    while (wifiSerial->available() > 0)
    {    
      if (wifiSerial->find("SEND OK"))
      {
        Serial.println(F("SEND OK"));
        resultado=0;
        break;
      }
      else 
        {
          Serial.println(F("SEND Failed"));
          resultado=1;        
        }
    }
  }
  else
  {
    Serial.println(F("POST not writed"));
    resultado=1;
  }
  post="";
  configurarWifi(ordenClose);
  
  return resultado;
}


//Recibimos la lista de ordenes para configurar
bool WifiBasic::configurarWifi(String *ordenes)
{
  Serial.println(F("--- configurarWifi()---"));
  uint8_t resultado=0;
  uint8_t i=0;
  while(ordenes[i]!="END")
  {
    orden(ordenes[i]);
    delay(3000);
    int valor = respuesta();
    Serial.print(F("configurarWifi()_rx_resultado:"));
    Serial.println(valor);
    if (valor!=0)   { resultado=1;}
    i++;
  }
  return resultado;
}


bool WifiBasic::orden(String comando)
{
  wifiSerial-> write(comando.c_str());
  wifiSerial-> write("\r\n");
  delay(3000);
}

bool WifiBasic::respuesta()
{
  Serial.println(F("respuesta()_"));
  String recibido ="";
  char c;
  int resultado=0;
  //Mientras haya datos en el serie de la wifi
  //El serie fuciona orientado a caracter
  while (wifiSerial-> available())
  {
    c=wifiSerial->read();  
    recibido += String(c);
  }
  Serial.println(F("** recibido_init"));
  Serial.print(recibido);
  Serial.println(F("** recibido_end"));
  if (
      recibido.endsWith F(("ERROR\r\n"))
    ||recibido.endsWith F(("FAIL\r\n"))
    ||recibido.endsWith F(("no ip\r\n"))
     )
        {
          resultado=1;
        }
  
  Serial.print(F("respuesta()_tx_resultado="));
  Serial.println(resultado);
  return resultado;

}







