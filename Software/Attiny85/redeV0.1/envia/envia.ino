#include <RF24Network.h>
#include <RF24.h>

RF24 radio(5,5);                    // COLOCAR OS VALORES IGUAIS QUANDO UTILIZAR O ATTINY E A BIBLIOTECA JA IRA RECONHECER COMO MODO DE 3 PINOS
                                    // O PINO 5 CORRESPONDE AO PINO DE RESET NO ATTINY, COLOQUEI DESSA FORMA PARA DEIXAR BEM CLARO QUE ELE NAO VAI
                                    // UTILIZAR NENHUM OUTRO PINO QUE NÃO SEJA OS 3 CORRESPONDENTES A COMUNICAÇÃO ICSP :)
   
RF24Network network(radio);          // Network uses that radio

const uint16_t hotspot = 01; // Endereço desse spot em Octal ou ID 01
const uint16_t base = 00; // Endereço da base em Octal
const unsigned long interval = 600; //ms // Frequência de envio dos dados
int teste=0;

struct  __attribute__ ((__packed__)) message_t {                  // Structure of our payload
  int id;
  int temperature;
  int luminosidade;
}; message_t message;

RF24NetworkHeader header(base);

void setup(void){
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  network.begin(/*channel*/ 90, /*node address*/ base);
}

void loop() {
  network.update();// Check the network regularly
  message.id = 01;
  int x;
  for (x=0; x<15; x++){
    message.temperature= analogRead(3) ;//APAGAR A3
    message.luminosidade= analogRead(4);//APAGAR A2
  }
  message = (message_t) {
     message.id, message.temperature/15, message.luminosidade/15
    }; // Ordem dos dados (ID, Temperatura, Umidade)
  header.type = 't';
  
 // RF24NetworkHeader header(/*to node*/ other_node);
  bool ok = network.write(header,&message,sizeof(message));

 delay(interval);
}

