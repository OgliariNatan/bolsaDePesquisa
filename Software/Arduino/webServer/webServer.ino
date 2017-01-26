#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h>

const char *ssid = "Any name you wish";
const char *pass = "your-secret-password";

ESP8266WebServer server(80);
String html = "<!DOCTYPE html><html><head>"\
"<meta name='viewport' content='width=device-width, initial-scale=1\'"\
"</head><body>"\
"<form method='GET' action='gpio2'>"\
"<button >Light</button><hr>"\
"</form>"\
"<h2>Light is ON</h2>"\
"</body></html>";

void start() {
  if(digitalRead(2)) {
    html.replace("ON", "OFF");
    server.send(200, "text/html", html);
  }
  else {
    html.replace("OFF", "ON");
    server.send(200, "text/html", html);
  }
}

void gpio2() {
  digitalWrite(2,!digitalRead(2));
  start();
}

void setup() {
  pinMode(2,1);
  digitalWrite(2,0);
  WiFi.softAPConfig({192,168,4,1},{192,168,4,1},{255,255,255,0});
  WiFi.softAP(ssid, pass);
  server.on("/", start);
  server.on("/gpio2", gpio2);
  server.begin();
}

void loop() {
  server.handleClient();
}
