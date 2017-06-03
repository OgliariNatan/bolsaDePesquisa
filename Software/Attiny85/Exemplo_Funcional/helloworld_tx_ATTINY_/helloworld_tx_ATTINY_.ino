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

struct __attribute__ ((__packed__)) payload_t {                  // Structure of our payload
  unsigned long ms;
  unsigned long counter;
};payload_t payload;

RF24NetworkHeader header(base);

void setup(void)
{
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  network.begin(/*channel*/ 90, /*node address*/ hotspot);
  pinMode(A2, OUTPUT);
}

void loop() {
    network.update();                          // Check the network regularly
    payload = (payload_t) { 54, 98 };
    header.type = 't';
    
     if (network.write(header, &payload, sizeof(payload))) {
      
     }
     teste = !teste;
    digitalWrite(A2, teste); 
    
  delay(interval);
}


