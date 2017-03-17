#include <SoftwareSerial.h>//bluetooth
const int ledPin = 13; //Led interno da placa
const int LDR = A3; //LDR no pino analígico 8 
const int LM35 = A6;

SoftwareSerial BTserial(10,11);// define RX/TX

void setup() {
 BTserial.begin(9600);
 pinMode(ledPin,OUTPUT); //define a porta 7 como saída
 
//Serial.begin(9600); //Inicia a comunicação serial
}
 
void loop() {
 int ldrValor = 0;
 float LM35Valor = 0;
 
 ldrValor = analogRead(LDR); //ler o valor do LDR, O valor lido será entre 0 e 1023
 LM35Valor = (float(analogRead(LM35))*5/(1023))/0.01;// Valor dado em °C
 
 //imprime o valor lido do LDR no monitor serial
 //Serial.print ("LDR: ");
 //Serial.println(ldrValor);
 // imprimi o valor lido do LM35 no monitor serial
 //Serial.print ("LM35: ");
 //Serial.println(LM35);
 
  BTserial.print("Temparatura");//Sensor 1
  BTserial.print(",");
  BTserial.print(LM35Valor);//Sensor 2
  BTserial.print(",");
  BTserial.print("°C & LUX");//Sensor 3
  BTserial.print(",");
  BTserial.print("LUX");//Sensor 4
  BTserial.print(",");
  BTserial.print(ldrValor);//Sensor 5
  BTserial.print(";");
 
  delay(500);
}
