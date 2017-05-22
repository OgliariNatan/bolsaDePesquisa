#include <RF24Network.h>
#include <RF24.h>
#include "tinySPI.h"
//#include <SPI.h>

#define HARDWARE_SPI 1 
//pin definitions
const int LATCH_PIN = 0;           //storage register clock (slave select)
const int DATA_PIN = 1;            //data in
const int CLOCK_PIN = 2;           //shift register clock
 
RF24 radio(7, 7);
RF24Network network(radio);

const uint16_t hotspot = 01; // Endereço desse spot em Octal ou ID
const uint16_t base = 00; // Endereço da base em Octal
const unsigned long interval = 600; //ms // Frequência de envio dos dados
// Estrutura da mensagem
struct message_t {
  int id;
  float temperature;
  float luminosidade;
};

message_t message;
RF24NetworkHeader header(base);
void setup(void)
{
  Serial.begin(57600);
  Serial.print("RF24Network / Node: ");
  Serial.println(hotspot);
  SPI.begin();
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  #if HARDWARE_SPI == 1
    SPI.begin();                   //start hardware SPI (the library sets up the clock and data pins)
  #else
    pinMode(CLOCK_PIN, OUTPUT);    //set up the pins for software SPI
    pinMode(DATA_PIN, OUTPUT);
  #endif
    pinMode(LATCH_PIN, OUTPUT);    //latch pin needs to be set up for hardware or software
    digitalWrite(LATCH_PIN, HIGH);

  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX); //Recomendo para módulo PA+LNA
  //radio.setDataRate(RF24_250KBPS); //Recomendável para longas distâncias
  network.begin(/*channel*/ 90, /*node address*/ hotspot);
}
void loop() {
  network.update(); // Verifica a rede regularmente
  float l = 9;//((analogRead (A0)*6.2364)-2785.6); //leitura da luminosidade  6,2364x - 2785,6
  float t = 8;//analogRead (A1); //leitura da temperatura
  message = (message_t) {
    hotspot, t, l
  }; // Ordem dos dados (ID, Temperatura, Umidade)
  header.type = 't';
  if (network.write(header, &message, sizeof(message))) {
    Serial.print("Mensagem enviada\n");
  } else {
    Serial.print("Não foi possível enviar\n");
  }
  // Aguarda envio
  delay(interval);
}
