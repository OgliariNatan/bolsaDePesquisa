const int ledPin = 13; //Led interno da placa
const int LDR = A3; //LDR no pino analígico 8 
const int LM35 = A6;

void setup() {
 pinMode(ledPin,OUTPUT); //define a porta 7 como saída
 Serial.begin(9600); //Inicia a comunicação serial
}
 
void loop() {
 ///ler o valor do LDR
 int ldrValor = 0;
 int LM35Valor = 0;
 ldrValor = analogRead(LDR); //O valor lido será entre 0 e 1023
 LM35Valor = analogRead(LM35); 
 //se o valor lido for maior que 500, liga o led
 if (ldrValor>= 800) digitalWrite(ledPin,HIGH);
 // senão, apaga o led
 else digitalWrite(ledPin,LOW);
 
 //imprime o valor lido do LDR no monitor serial
 Serial.print ("LDR: ");
 Serial.println(ldrValor);
 delay(100);
}
