
#define BPSW 9600

String ordenesAT[]=
{
  "AT",
  "AT+CWMODE=1",//modo cliente de red
  // "AT+CWJAP=\"DELABS\",\"dellmacmolaano\"",
  "AT+CWJAP=\"casaelobrero\",\"lacosamasbonitadelmundo\"",
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
  "AT+CIPSTART=\"TCP\",\"192.168.1.128\",9090",
  "END"
};

// ******************************
// ********** clases ************
// ******************************

class WifiBasic {
  private:
  int wifi_conected;
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
// ******* deficnicion de dunciones  *******
// ****************************************

WifiBasic::WifiBasic(SoftwareSerial* _wifiSerial)
{
  wifiSerial= _wifiSerial;
  wifi_conected = 1; //wifi no conectada
  wifiSerial->begin(BPSW);
  
}


bool WifiBasic::enviarPost(String name, String value)
{
  // void fpost( String output)
  // entrara nombre y valor

  
  int resultado;

  
  Serial.println("---------- orden(AT+CWJAP)--");
  orden("AT+CWJAP?");
  
  if (wifiSerial->find("ERROR")) 
    {
      Serial.println("encontroado ERROR en CWJAP");
      wifi_conected = 1;
    }

  Serial.print("algoritmo: wifi_conected= ");
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
  Serial.println ("cuerpo_parte_1");
  Serial.println (cuerpo);
  String lonPost = String(cuerpo.length());
  Serial.println ("cuerpo_parte_lonPost");
  Serial.println (lonPost);
  
 
  String post = "POST / HTTP/1.1\r\nContent-Length:" + lonPost + "\r\n\r\n"+ cuerpo;
  cuerpo="";

  Serial.println ("post_total= cabecera + cuerpo");
  Serial.println (post);
  
  // envia el post
  String comando= "AT+CIPSEND=";
  Serial.println(comando+post.length());

  // envar comando al modulo wifi
  wifiSerial->print(comando.c_str());
  wifiSerial->println(post.length());
  

  delay(1000);
  if (wifiSerial->find(">"))
  
  {
    Serial.println("---- > --");
    wifiSerial-> write(post.c_str());
    wifiSerial-> write("\r\n");
    delay(3000);
    int resultado = respuesta();
    delay(100);
    while (wifiSerial->available() > 0)
    {    
      if (wifiSerial->find("SEND OK"))
      {
        Serial.println("SEND OK");
        resultado=0;
        break;
      }
      else 
        {
          Serial.println("SEND Failed");
          resultado=1;        
        }
    }
  }
  else
  {
    Serial.println("POST not writed");
    resultado=1;
  }
  post="";
  configurarWifi(ordenClose);
  
  return resultado;
}


//Recibimos la lista de ordenes para configurar
bool WifiBasic::configurarWifi(String *ordenes)
{
  Serial.println("---------- configurarWifi() --");
  uint8_t resultado=0;
  uint8_t i=0;
  while(ordenes[i]!="END")
  {
    orden(ordenes[i]);
    delay(4000);
    int valor = respuesta();
    Serial.print("configurarWifi()_rx_resultado:");
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
  Serial.println("rspuesta()_");
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
  Serial.println("** recibido_init");
  Serial.print(recibido);
  Serial.println("** recibido_end");
  if (
      recibido.endsWith("ERROR\r\n")
    ||recibido.endsWith("FAIL\r\n")
    ||recibido.endsWith("no ip\r\n")
     )
        {
          resultado=1;
        }
  
  Serial.print("respuesta()_tx_resultado=");
  Serial.println(resultado);
  return resultado;

}







