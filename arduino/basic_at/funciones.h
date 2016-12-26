/*
Para enviar un comando a la wifi
*/

bool orden(String comando)
{
  wifiSerial.write(comando.c_str());
  wifiSerial.write("\r\n");
}

bool respuesta()
{
  String comando;
  char c;
  int resultado=1;
  //Mientras haya datos en el serie de la wifi
  //El serie fuciona orientado a caracter
  while (wifiSerial.available())
  {
    c=wifiSerial.read();  
    comando += String(c);
  }
  Serial.println(comando);
  if (!comando.equalsIgnoreCase("error"))
  {
    resultado=0;
  }
  return resultado;
  
}
//Recibimos la lista de ordenes para configurar
bool configurarWifi(String *ordenes)
{
  uint8_t resultado=0;
  uint8_t i=0;
  while(ordenes[i]!="END")
  {
    orden(ordenes[i]);
    delay(4000);
    int valor = respuesta();
    Serial.print("Respuesta:");
    Serial.println(valor);
    if (valor!=0)
    {
      
      resultado=1;
    }
    i++;
  }
  return resultado;
}

void fpost( String output)
{
  String comando= "AT+CIPSEND=";
  Serial.println(comando+output.length());
  wifiSerial.print(comando.c_str());
  wifiSerial.println(output.length());
  

  delay(100);
  if (wifiSerial.find(">"))
  {
    Serial.println("listo para enviar");
    wifiSerial.write(output.c_str());
    wifiSerial.write("\r\n");
    delay(10);
    while (wifiSerial.available() > 0)
    {
      if (wifiSerial.find("SEND OK"))break;
    }
  }
  else
  {
    Serial.println("no escrito");
  }
}


bool enviarPost(String *post)
{
  uint8_t resultado=0;
  uint8_t i=0;
  while (post[i]!="END")
  {
    fpost(post[i]);
    Serial.println(post[i]);
    delay(1000);
    int valor = respuesta();
    Serial.print("post???");
    Serial.println(valor);
    {
      resultado=1;
    }
    i++;
  }
  return resultado;
}



String recibido()
{
 String comando="";
  char c;
  //Orientado a caracter.
  while (wifiSerial.available())
  {
    c=wifiSerial.read();  
    comando += String(c);
  }//se sale cuando recibe un fina de linea \r\n
  return comando;
}






