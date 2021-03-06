#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(9, 10);
RF24Network network(radio); // Define o rádio para Network
const uint16_t base = 00; // Endereço base em octal (Deixar 00 para ser base)

// Estrutura dos dados
struct message_t {
  int id;
  float temperature;
  float luminosidade;
};

void setup(void){
  Serial.begin(57600);
  
  //nRF
  SPI.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MAX); //Recomendo para módulo PA+LNA
  //radio.setDataRate(RF24_250KBPS); //Recomendável para longas distâncias
  //RF24Network
  network.begin(/*Canal*/ 90, /*Endereço*/ base);
}
void loop(void) {
  network.update(); // Verifica a rede regularmente
  while ( network.available() ) { // Tem novos dados na rede?
    RF24NetworkHeader header; // Se tem, pega e mostra os dados na serial.
    message_t message;
    network.read(header, &message, sizeof(message));
    Serial.print(message.id);
    Serial.print("\t");
    Serial.print(message.temperature);
    Serial.print("\t");
    Serial.println(message.luminosidade);
  }
}
