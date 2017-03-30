#include <SoftwareSerial.h>//bluetooth
#define ledPin 13   //Led interno da placa
#define LDR    A3   //LDR no pino analígico 8 
#define LM35   A6
#define n      5    //Valor de aquisições para realizar a media dos valores
#define tempo_n  100// intervalo entre as leituras

SoftwareSerial BTserial(10, 11); // define RX/TX

void updateBluetooth (float LM35Valor, int ldrValor);// Função de transferencia de dados para o Bluetooth
void readIO (float *LM35Valor, int *ldrValor); // Função ler I/O

void setup() {
  BTserial.begin(9600);
  pinMode(ledPin, OUTPUT); //define a porta 13 como saída
  //analogReference(DEFAULT); //APAGAR

  //Serial.begin(9600); //Inicia a comunicação serial
}

void loop() {
  int   ldrValor  = 0;
  float LM35Valor = 0;

  readIO (&LM35Valor, &ldrValor);
  updateBluetooth (LM35Valor, ldrValor);

  //delay(500);
}
void readIO (float *LM35Valor, int *ldrValor) {
  int x;
  for (x = 0; x < n; x++) {
    *ldrValor = *ldrValor + analogRead(LDR); //ler o valor do LDR, O valor lido será entre 0 e 1023
    *LM35Valor = *LM35Valor + ((float(analogRead(LM35)) * 5 / (1023)) / 0.01 ); // Valor dado em °C, """Não Calibrado"""""
    delay (tempo_n);
  }
  x = 0;
  *ldrValor = *ldrValor / n;
  *LM35Valor = *LM35Valor / n;
}

void updateBluetooth (float LM35Valor, int ldrValor) { //Função que envia os dados para o smartphone
  BTserial.print("Temparatura");//Sensor 1
  BTserial.print(",");
  BTserial.print(LM35Valor);//Sensor 2
  BTserial.print(",");
  BTserial.print("LUX");//Sensor 3
  BTserial.print(",");
  BTserial.print(6.2516*ldrValor - 2795.3); //Sensor 4  6.2364 * ldrValor - 2785.6
  //BTserial.print(",");
  //BTserial.print(ldrValor);//Sensor 5
  BTserial.print(";");
}
