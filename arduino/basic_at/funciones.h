/*
Para enviar un comando a la wifi
*/

bool orden(String comando)
{
  wifiSerial.write(comando.c_str());
  wifiSerial.write("\r\n");
  delay(3000);
}

bool respuesta()
{
  Serial.println("rspuesta()_");
  String recibido ="";
  char c;
  int resultado=0;
  //Mientras haya datos en el serie de la wifi
  //El serie fuciona orientado a caracter
  while (wifiSerial.available())
  {
    c=wifiSerial.read();  
    recibido += String(c);
  }
  Serial.println("** recibido_init");
  Serial.print(recibido);
  Serial.println("** recibido_end");
  if (recibido.endsWith("ERROR\r\n")||recibido.endsWith("FAIL\r\n"))
    {
      resultado=1;
    }
  
  Serial.print("respuesta()_tx_resultado=");
  Serial.println(resultado);
  return resultado;
  
}
//Recibimos la lista de ordenes para configurar
bool configurarWifi(String *ordenes)
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

void fpost( String output)
{
  
  String comando= "AT+CIPSEND=";
  
  // imprimir conando a enviar
  Serial.println(comando+output.length());

  // envar comando al modulo wifi
  wifiSerial.print(comando.c_str());
  wifiSerial.println(output.length());
  

  delay(1000);
  if (wifiSerial.find(">"))
  
  {
    Serial.println("---- > --");
    wifiSerial.write(output.c_str());
    wifiSerial.write("\r\n");
    delay(10);
    while (wifiSerial.available() > 0)
    {    
      if (wifiSerial.find("SEND OK"))
      {
        Serial.println("SEND OK");
        break;
      }
      else Serial.println("SEND Failed");
    }
 
  }
  else
  {
    Serial.println("POST not writed");
  }
}


bool enviarPost(String *post)
{
  Serial.println("---------- enviarPost() --");
  uint8_t resultado=0;
  uint8_t i=0;
  while (post[i]!="END")
  {
    fpost(post[i]);
    Serial.println(post[i]);
    delay(1000);
    int valor = respuesta();
    Serial.println(valor);
    {
      resultado=valor;
    }
    i++;
  }
  return resultado;
}




