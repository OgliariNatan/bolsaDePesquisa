#include <SoftwareSerial.h>//bluetooth
const int ledPin = 13; //Led interno da placa
const int LDR = A3; //LDR no pino analígico 8 
const int LM35 = A6;
const int n = 5; //Valor de aquisições para realizar a media dos valores
const int tempo_n = 100;

SoftwareSerial BTserial(10,11);// define RX/TX

void updateBluetooth (float LM35Valor, int ldrValor);// Função de transferencia de dados para o Bluetooth


void setup() {
 BTserial.begin(9600);
 pinMode(ledPin,OUTPUT); //define a porta 7 como saída
 
//Serial.begin(9600); //Inicia a comunicação serial
}
 
void loop() {
 int ldrValor = 0;
 float LM35Valor = 0;
 
 int x;
 for (x=0; x<n; x++){
    ldrValor = ldrValor + analogRead(LDR); //ler o valor do LDR, O valor lido será entre 0 e 1023
    LM35Valor = LM35Valor + ((float(analogRead(LM35))*5/(1023))/0.01 );// Valor dado em °C, """Não Calibrado"""""
    delay (tempo_n);
 }
  x = 0;
  ldrValor = ldrValor / n;
  LM35Valor = LM35Valor / n;
 
  updateBluetooth(LM35Valor, ldrValor);
 
  //delay(500);
return 0;
}


void updateBluetooth (float LM35Valor, int ldrValor){//Função que envia os dados para o smartphone
  BTserial.print("Temparatura");//Sensor 1
  BTserial.print(",");
  BTserial.print(LM35Valor);//Sensor 2
  BTserial.print(",");
  BTserial.print("LUX");//Sensor 3
  BTserial.print(",");
  BTserial.print(6.2364*ldrValor-2785.6);//Sensor 4
  //BTserial.print(",");
  //BTserial.print(ldrValor);//Sensor 5
  BTserial.print(";");
  
 return 0;
  }

 //imprime o valor lido do LDR no monitor serial
 //Serial.print ("LDR: ");
 //Serial.println(ldrValor);
 // imprimi o valor lido do LM35 no monitor serial
 //Serial.print ("LM35: ");
 //Serial.println(LM35);
