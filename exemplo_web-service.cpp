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
  // Cria a string de resposta em JSON
  String s = "HTTP/1.1 200 OK\r\n";
  //s += "Access-Control-Allow-Origin: *\r\n";
  s += "Content-Type: application/json;charset=utf-8\r\n\r\n";
  s += "{";
  s += "'webservice': 'ok'";
  s += "}";
  // Envia uma resposta ao cliente
  client.print(s);
  delay(1);
  // O cliente eh desconectado 
  // quando a funcao retornar e o objeto 'client' for destruido
}
