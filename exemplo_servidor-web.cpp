#include <ESP8266WiFi.h>

const char* ssid = "seu-ssid";
const char* password = "sua-senha";

// define web server port
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  // start server
  server.begin();

}

void loop() {
  // check if someone client is connect
  WiFiClient client = server.available();
  if (!client) {
    delay(100);
    return;
  }
  // read first line from request
  String req = client.readStringUntil('\r');
  client.flush();
  // send response to client
  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n
  	\r\n<!DOCTYPE HTML>\r\n<html>\r\nMensagem de resposta</html>\n");
  delay(1);
  // client is disconnect
  // when function ends and client object is destroyd
}
