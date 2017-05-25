#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int transmitterId;

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10
//Contacts from the radio to connect NRF24L01 pinamnam -> Arduino

//SCK -> 13
//MISO -> 12
//MOSI -> 11
//CSN -> 10
//CE -> 9

RF24 radio(9, 10);

// this is not the channel address, but the transmitter address
const uint64_t pipe = 0xE8E8F0F0E1LL;

//button connected to these pins

int buttonPin1 = 2;

void setup(void) {
  Serial.begin(9600);
  

  // CHANGE THIS PER EACH TRANSMITTER, from 0 to 4
  transmitterId = 0;

  radio.begin();

  // the following statements improve transmission range
  radio.setPayloadSize(2); // setting the payload size to the needed value
  radio.setDataRate(RF24_250KBPS); // reducing bandwidth

  radio.openWritingPipe(pipe); // set the transmitter address

}

void loop(void) {
  Serial.println("esta no loop");

  //until the button (buttonPin1) pressed send the package (id) to receiver Arduino
  if (digitalRead(buttonPin1) == LOW) {
    Serial.println("Esta LENDO");

    // some implementations automatically shut down the radio after a transmission: this
    // ensures the radio is powered up before sending data
    radio.powerUp();

    // read and write expect a reference to the payload (& symbol)
    // second argument is the packet length in bytes (sizeof(int) == 2)
    int c;
    c = radio.write(&transmitterId, 2);
    delay(600);
  }
}
