#define CE_PIN 9
#define CSN_PIN 10

#include <SPI.h>
#include "RF24.h"

RF24 radio(CE_PIN, CSN_PIN);

uint64_t address = 0xE14BC8F482LL; //byte address[11] = "SimpleNode";
unsigned long payload = 0;

void setup() {
  Serial.begin(115200);
  radio.begin(); // Start up the radio
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openReadingPipe(1, address); // Write to device address 'SimpleNode'
  radio.startListening();
}

void loop(void){
  radio.stopListening();
  radio.startListening();
  radio.read( &payload, sizeof(unsigned long) );
  if(payload != 0){
    Serial.print("Got Payload ");
    Serial.println(payload);
  }
  delay(1000);
}
