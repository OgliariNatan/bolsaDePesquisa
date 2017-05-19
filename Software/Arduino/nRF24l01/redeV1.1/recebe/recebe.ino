#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <avr/wdt.h>

#define DEBUG //!<Ativa a depuração

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
  SPI.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MAX); //Recomendo para módulo PA+LNA
  //radio.setDataRate(RF24_250KBPS); //Recomendável para longas distâncias
  //RF24Network
  network.begin(/*Canal*/ 90, /*Endereço*/ base);
  wdt_enable(WDTO_2S); //Função que ativa e altera o Watchdog
}
void loop(void) {
  wdt_reset();//zera o wdt
  network.update(); // Verifica a rede regularmente
  while ( network.available() ) { // Tem novos dados na rede?
    RF24NetworkHeader header; // Se tem, pega e mostra os dados na serial.
    message_t message;
    network.read(header, &message, sizeof(message));
    Serial.print("ID: ");
    Serial.println(message.id);
    Serial.print("Temperatura: ");
    Serial.println(message.temperature);
    Serial.print("Luminosidade: ");
    Serial.println(message.luminosidade);
  }
}
