#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <DS1307.h>
#include <math.h>

#define DEBUG //!<Ativa a depuração

//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(A4, A5);

//ligação do nrf
RF24 radio(9, 10);
RF24Network network(radio);

const uint16_t hotspot = 01; // Endereço desse spot em Octal ou ID 01
const uint16_t base = 00; // Endereço da base em Octal
const unsigned long interval = 600; //ms // Frequência de envio dos dados

// Estrutura da mensagem 
struct __attribute__ ((__packed__)) message_t {
  int id;
  float temperature;
  float luminosidade;
  //char hora;
  //char data;//no formato xxxxxx -> sendo ddmmaa
}; message_t message;

RF24NetworkHeader header(base);

void updateIO (float* l, float* t);
void relogio (void);

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
  //relogio ();
}


void loop() {
  network.update(); // Verifica a rede regularmente
  char data, hora;// ,semana;
  float l, t;
  updateIO (&l, &t);
  
  hora = rtc.getTimeStr();
  data = rtc.getDateStr();//FORMAT_SHORT
  //semana = rtc.getDOWStr();//FORMAT_SHORT
  
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
       Serial.print("Hora: ");    
       Serial.println(hora);
       Serial.print("Data: ");    
       Serial.println(data);
       Serial.println("-----------------------");
     #endif /// DEBUG
}
//Atualiza a leitura dos pinos
void updateIO (float* l, float* t){
  
  *l = ((analogRead (A0)*6.2364)-2785.6); //leitura da luminosidade  6,2364x - 2785,6
  *t =  112900+23400*log10(analogRead(A1)/0.000185)+880000000*(log10(analogRead(A1)/0.000185))*(log10(analogRead(A1)/0.000185)); //leitura da temperatura analogRead (A1)
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
  
