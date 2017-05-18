// Programa : NRF24L01 Emissor - Servo motor
// Autor : Arduino e Cia

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Armazena caractere digitado na serial
char valor[1];

// Armazena os dados enviados
int dados[1];

// Inicializa o NRF24L01 nos pinos 9 (CE) e 10 (CS) do Arduino Uno
RF24 radio(9,10);

// Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE13CBAF433LL;

void setup()
{
  // Inicializa a serial
  Serial.begin(57600);
  Serial.println("Digite 1, 2 ou L e pressione ENVIAR...");
  
  // Inicializa a comunicacao do NRF24L01
  radio.begin();
  // Entra em modo de transmissao
  radio.openWritingPipe(pipe);
}

void loop()
{
  // Le o caractere digitado na serial
  if (Serial.available() > 0) 
  {
    valor[0] = Serial.read();
  }
  
  // Envia 1 via radio caso seja digitado o valor 1
  if (valor[0] == '1')
  {
    Serial.println("Enviado : 1 - Gira servo para a esquerda");
    dados[0] = 1;
    radio.write(dados, 1);
    delay(100);
    valor[0] = 0;
  }
  
  // Envia 2 via radio caso seja digitado o valor 2
  if (valor[0] == '2')
  {
    Serial.println("Enviado : 2 - Gira servo para a direita");
    dados[0] = 2;
    radio.write(dados, 1);
    delay(100);
    valor[0] = 0;
  }
  
  // Envia 3 via radio caso seja digitado o caractere L
  if (valor[0] == 'L')
  {
    Serial.println("Enviado : L - Acende o led");
    dados[0] = 3;
    radio.write(dados, 1);
    delay(100);
    valor[0] = 0;
  }
}