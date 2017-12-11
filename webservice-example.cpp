#include <ESP8266WiFi.h>

const char* ssid = "some-ssid";
const char* password = "some-password";

// define web service port
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
  // create string to response in JSON
  String s = "HTTP/1.1 200 OK\r\n";
  //s += "Access-Control-Allow-Origin: *\r\n";
  s += "Content-Type: application/json;charset=utf-8\r\n\r\n";
  s += "{";
  s += "'webservice': 'ok'";
  s += "}";
  // send response to client
  client.print(s);
  delay(1);
  // client is disconnect
  // when function ends and client object is destroyd
}
