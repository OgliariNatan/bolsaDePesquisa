#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

#define DEBUG //!<Ativa a depuração

RF24 radio(9, 10);
RF24Network network(radio);

const uint16_t hotspot = 01; // Endereço desse spot em Octal ou ID 01
const uint16_t base = 00; // Endereço da base em Octal
const unsigned long interval = 600; //ms // Frequência de envio dos dados

// Estrutura da mensagem
struct message_t {
  int id;
  float temperature;
  float luminosidade;
  int hora;
  int minuto;
  int data;//no formato xxxxxx -> sendo ddmmaa
}; message_t message;

RF24NetworkHeader header(base);


void setup(void)
{
  Serial.begin(57600);
  Serial.print("RF24Network / ID: ");
  Serial.println(hotspot);
  SPI.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MAX); //Recomendo para módulo PA+LNA
  //radio.setDataRate(RF24_250KBPS); //Recomendável para longas distâncias
  network.begin(/*channel*/ 90, /*node address*/ hotspot);
}


void loop() {
  network.update(); // Verifica a rede regularmente
  float l = ((analogRead (A0)*6.2364)-2785.6); //leitura da luminosidade  6,2364x - 2785,6
  float t = analogRead (A1); //leitura da temperatura
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

     #ifdef DEBUG
       Serial.println("-----------------------");
       Serial.print("ID: ");    
       Serial.println(message.id);
       Serial.print("Temparatura: ");    
       Serial.println(message.temperature);
       Serial.print("Luminosidade: ");    
       Serial.println(message.luminosidade);
       Serial.println("-----------------------");
     #endif /// DEBUG
}
