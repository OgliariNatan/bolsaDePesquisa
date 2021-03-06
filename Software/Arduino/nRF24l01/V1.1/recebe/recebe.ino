// Programa : NRF24L01 Receptor - Servo motor

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h> 
#include <avr/wdt.h>

#define DEBUG //!<Ativa a depuração

// Armazena os dados recebidos
int recebidos[1];

// Inicializa o NRF24L01 nos pinos 9 (CE) e 53 (CS) do Arduino Mega
RF24 radio(9,10);

Servo myservo;

// Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE13CBAF433LL;

// Define o pino do led
int LED1 = 3;

void setup()
{
  // Servo conectado ao pino 4
  myservo.attach(4);
  // Define o pino do led como saida
  pinMode(LED1, OUTPUT);
  // Inicializa a serial
  Serial.begin(57600);
  // Inicializa a comunicacao do NRF24L01
  radio.begin();
  // Entra em modo de recepcao
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  // Mensagem inicial
  Serial.println("Aguardando dados...");
  wdt_enable(WDTO_2S); //Função que ativa e altera o Watchdog 2 4 8
}

void loop()
{
  recebidos[0] = 0;
  //Serial.println("Esta no loop");
  // Verifica sinal de radio
  if (!radio.available())
  {

    #ifdef DEBUG
      Serial.println("Esta no radio");
    #endif /// DEBUG
      
    int done = 0;// COLOCAR ZERO    
    while (!done)   {
      //done = radio.read(recebidos, 1);
      radio.read(recebidos, 1);
      
      
      #ifdef DEBUG
        Serial.println("-----------------------");
        Serial.print("Recebido[0]: ");    
        Serial.println(recebidos[0]);
        Serial.print("Recebido[1]: ");    
        Serial.println(recebidos[1]);
        Serial.println("-----------------------");
      #endif /// DEBUG
      
      // Se recebeu 1, movimenta o servo para a esquerda
      if (recebidos[0] == 1)    {
        delay(10);
        Serial.println(" -> Girando motor para a esquerda");
        myservo.write(0);//1
      }
      
      // Se recebeu 2, movimenta o servo para a direita
      if (recebidos[0] == 2){
        delay(10);
        Serial.println(" -> Girando motor para a direita");
        myservo.write(160);//160
      }

      // Se recebeu 3, acende o led
      if (recebidos[0] == 3) {
        delay(10);
        Serial.println(" -> Acende led");
        digitalWrite(LED1, HIGH);
      }
      if (recebidos[0] == 4) {
        delay(10);
        Serial.println(" -> Apaga led");
        digitalWrite(LED1, LOW);
      }
      delay(500);
      wdt_reset();//zera o wdt
    }
  }
  wdt_reset();//zera o wdt
}
