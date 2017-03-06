
// *******************************************************
// ******** CONFIGURACION WIFI ********
// *******************************************************


// #define SSID "Invitados"
// #define PASS ""
// #define SSID "movil-oscar"
// #define PASS "Latorre64"
#define SSID "casaelobrero"
#define PASS "lacosamasbonitadelmundo"
// #define SSID "ENDEF"
// #define PASS "87654321"
 
// #define SSID "DELABS"
// #define PASS "dellmacmolaano"
#define IP "193.146.117.35"
#define PORT "7000"


// *******************************************************
#define RST 7

String ssid = SSID;
String pass = PASS;


  String ordenesAT[]=
{
  "AT+CWMODE=1",//modo cliente de red
  "AT+CWJAP=\"" +  ssid +"\",\"" + pass + "\"",
  "AT+CIPMUX=0",//Simple conexión 
  "AT+CIFSR",//ip asignada 
  "END"
};

/*
String ordenClose[]=
{
  "AT+CIPCLOSE=0",
  "END"
};

String ordenConexion[]=
{
  // "AT+CIPSTART=\"TCP\",\"192.168.2.221\",9090",
  // "AT+CIPSTART=\"TCP\",\"192.168.1.128\",9090",
  // "AT+CIPSTART=\"TCP\",\"193.146.117.35\",7000",
  "AT+CIPSTART=\"TCP\",\"" + ip + "\"," + port,
  "END"
};

*/


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
  bool configurarWifi(String *ordenes);  
  bool orden(String comando);
  bool respuesta();
  void pinReset();

  
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
  
  uint8_t resultado;

  orden(F("AT+CWJAP?"));
  
  if (wifiSerial->find(SSID)) 
    {
      Serial.println("encontroado SSID");
      wifi_conected = 0;
    }

    else
    {
      Serial.println("No encontrado SSID");
      wifi_conected = 1;
    }

  Serial.print(F("algoritmo: wifi_conected= "));
  Serial.print(wifi_conected);
  Serial.println(F(" (0 -> conected)"));
  
  // orden("AT+CWJAP?");
  // respuesta();

  if(wifi_conected != 0)
  {
      wifi_conected = 0;
      pinReset();
      configurarWifi(ordenesAT);  
  }

  // configurarWifi(ordenConexion);
  String ip = (F(IP));
  String port =(F(PORT));
  orden( "AT+CIPSTART=\"TCP\",\"" + ip + "\"," + port);
  respuesta();
  delay(1000);

  String cuerpo = "name=" + name + "&value=" + value;
  String lonPost = String(cuerpo.length());
  // Serial.println (F("cuerpo_parte_1"));
  // Serial.println (cuerpo); 
  // Serial.println (lonPost);
  
 
  String post = ("POST / HTTP/1.1\r\nContent-Length:") + lonPost + "\r\n\r\n"+ cuerpo;

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
  // configurarWifi(ordenClose);

  orden("AT+CIPCLOSE=0");
  respuesta();
  
  return resultado;
}


//Recibimos la lista de ordenes para configurar
bool WifiBasic::configurarWifi(String *ordenes)
{
  Serial.println(F("configurarWifi() ***** "));
  uint8_t resultado=0;
  uint8_t i=0;
  while(ordenes[i]!="END")
  {
    // Serial.println(ordenes[i]);
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
  Serial.println(comando);
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

void WifiBasic::pinReset () {
   Serial.print(F("Inicio reset **** "));
   pinMode (RST, OUTPUT);
   digitalWrite (RST, LOW);
   delay (1000);
   digitalWrite (RST, HIGH);
   delay (4000);
   Serial.print(F("Final reset **** "));
}







