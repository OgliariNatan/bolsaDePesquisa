#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

#define DEBUG //!<Ativa a depuração
RF24 radio(9,10);                // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);      // Network uses that radio
const uint16_t base = 00; // Endereço base em octal (Deixar 00 para ser base)

struct  __attribute__ ((__packed__)) payload_t { // Structure of our payload
  unsigned long ms;
  unsigned long counter;
};

void setup(void)

{
  Serial.begin(57600);
  SPI.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  network.begin(/*channel*/ 90, /*node address*/ base);
  Serial.println("SETUP");
}

void loop(void){
  network.update();                  // Check the network regularly
   
  while ( network.available() ) {     // Is there anything ready for us?
    RF24NetworkHeader header;        // If so, grab it and print it out
    payload_t payload;
    network.read(header, &payload, sizeof(payload));
    Serial.print("Received packet: ");
    Serial.println(payload.counter);
    Serial.print(" at ");
    Serial.println(payload.ms);
  }
}

