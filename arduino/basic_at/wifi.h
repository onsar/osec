
/*
Configuración de la wifi
*/
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

String ordenPost[]=
{
  "POST / HTTP/1.1\r\nContent-Length: 14\r\n\r\ntemperatura=14\r\n",
  "END"
};

