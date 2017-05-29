#include <RF24Network.h>
#include <RF24.h>

RF24 radio(5,5);                    // COLOCAR OS VALORES IGUAIS QUANDO UTILIZAR O ATTINY E A BIBLIOTECA JA IRA RECONHECER COMO MODO DE 3 PINOS
                                    // O PINO 5 CORRESPONDE AO PINO DE RESET NO ATTINY, COLOQUEI DESSA FORMA PARA DEIXAR BEM CLARO QUE ELE NAO VAI
                                    // UTILIZAR NENHUM OUTRO PINO QUE NÃO SEJA OS 3 CORRESPONDENTES A COMUNICAÇÃO ICSP :)
   
RF24Network network(radio);          // Network uses that radio

const uint16_t base = 00;        // Address of our node in Octal format
const uint16_t other_node = 00;       // Address of the other node in Octal format

const unsigned long interval = 600; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already


struct  __attribute__ ((__packed__)) message_t {                  // Structure of our payload
  int id;
  float temperature;
  float luminosidade;
}; message_t message;

void setup(void)
{
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ base);
}

void loop() {
  network.update();                          // Check the network regularly
  message.temperature=1;//APAGAR
  message.luminosidade=2;//APAGAR
  unsigned long now = millis();              // If it's time to send a message, send it!
  //if ( now - last_sent >= interval  )
  //{
    last_sent = now;
    message = (message_t) {
    message.id, message.temperature, message.luminosidade
  }; // Ordem dos dados (ID, Temperatura, Umidade)
    RF24NetworkHeader header(/*to node*/ other_node);
    bool ok = network.write(header,&message,sizeof(message));
 // }
 delay(interval);
}

