#include <ESP8266WiFi.h>

const char* ssid = "seu-ssid";
const char* password = "sua-senha";

// define a porta do servidor web
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  // Inicia o servidor
  server.begin();

}

void loop() {
  // Checa se algum cliente conectou
  WiFiClient client = server.available();
  if (!client) {
    delay(100);
    return;
  }
  // Le a primeira linha da requisicao
  String req = client.readStringUntil('\r');
  client.flush();
  // Envia uma resposta ao cliente
  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n
  	\r\n<!DOCTYPE HTML>\r\n<html>\r\nMensagem de resposta</html>\n");
  delay(1);
  // O cliente eh desconectado 
  // quando a funcao retornar e o objeto 'client' for destruido
}
