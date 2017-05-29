#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <DS1307.h>

//#define DEBUG //!<Ativa a depuração

//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(A4, A5);

RF24 radio(9, 10);
RF24Network network(radio); // Define o rádio para Network
const uint16_t base = 00; // Endereço base em octal (Deixar 00 para ser base)

// Estrutura dos dados
struct __attribute__ ((__packed__)) message_t {
  int id;
  float temperature;
  float luminosidade;
  //char hora;
  //char data;//no formato xxxxxx -> sendo ddmmaa
}; message_t message;

void relogio (void);

void setup(void){
  Serial.begin(57600);
  SPI.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MAX); //Recomendo para módulo PA+LNA
  //radio.setDataRate(RF24_250KBPS); //Recomendável para longas distâncias
  //RF24Network
  network.begin(/*Canal*/ 90, /*Endereço*/ base);
}
void loop(void) {
  network.update(); // Verifica a rede regularmente

  char data, hora;// ,semana; //APAGAR
  //relogio ();
  
  while ( network.available() ) { // Tem novos dados na rede?
    RF24NetworkHeader header; // Se tem, pega e mostra os dados na serial.
    
    network.read(header, &message, sizeof(message));
    Serial.print("ID: ");
    Serial.println(message.id);
    Serial.print("Temperatura: ");
    Serial.println(message.temperature);
    Serial.print("Luminosidade: ");
    Serial.println(message.luminosidade);

    //Serial.print("Hora: ");    
    //Serial.println(hora);
    //Serial.print("Data: ");    
    //Serial.println(data);
  }
}

//configura o relogio
void relogio (void){
  rtc.halt(0);
  rtc.setDOW(FRIDAY);
  rtc.setTime(20, 29, 53);
  rtc.setDate(6, 6, 6);

  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(1);
  }
