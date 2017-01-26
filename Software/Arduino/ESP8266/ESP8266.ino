/*Codigo teste para iluminaria inteligente
 * 
 * autor: 
 */
#include <ESP8266WiFi.h>
#include "aREST.h"
#include "aREST_UI.h"
 int h, d, w;

// Create aREST instance
aREST_UI rest = aREST_UI();

// WiFi parameters
const char* ssid = "Nei_Mhnet";
const char* password = "no275no8";

// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);
void setup(void)
{  
  // Start Serial
  Serial.begin(115200);
  
  // Create UI
  rest.title("Relay Control");
  rest.button(5);
    
  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("esp8266");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
  
}

void loop() {
  
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
 
}
