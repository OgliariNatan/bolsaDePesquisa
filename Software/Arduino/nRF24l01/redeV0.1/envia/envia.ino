//#include <DHT.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

//#define DHTPIN 3
// Selecionar qual DHT está usando, houve notável instabilidade ao usar o DHT11
//#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
//DHT dht(DHTPIN, DHTTYPE);

RF24 radio(9, 10);
RF24Network network(radio);

const uint16_t hotspot = 01; // Endereço desse spot em Octal
const uint16_t base = 00; // Endereço da base em Octal
const unsigned long interval = 1000; //ms // Frequência de envio dos dados
// Estrutura da mensagem
struct message_t {
  int id;
  float temperature;
  float humidity;
};

message_t message;
RF24NetworkHeader header(base);
void setup(void)
{
  Serial.begin(57600);
  // +5V para o DHT
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  //dht.begin(); // data pin 3
  Serial.print("RF24Network / User: Jhonatan / Node: ");
  Serial.println(hotspot);
  SPI.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MAX); //Recomendo para módulo PA+LNA
  //radio.setDataRate(RF24_250KBPS); //Recomendável para longas distâncias
  network.begin(/*channel*/ 90, /*node address*/ hotspot);
}
void loop() {
  network.update(); // Verifica a rede regularmente
  float h = 25; //dht.readHumidity(); // Lê a umidade
  float t = 94;//dht.readTemperature(); // Lê a temperatura em Celsius
  message = (message_t) {
    hotspot, t, h
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
