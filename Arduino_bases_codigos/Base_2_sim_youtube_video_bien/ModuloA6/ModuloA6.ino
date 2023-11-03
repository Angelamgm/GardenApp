
#include <SoftwareSerial.h> 
SoftwareSerial A6MODULE(2,3); //rx tx

void setup() {
 Serial.begin(9600);
 Serial.println("Arduino Ok!");

 pinMode(8, OUTPUT);
 digitalWrite(8,LOW);
 delay(5000);
 Serial.println("Activando modulo A6...");
 digitalWrite(8,HIGH);
 delay(1000);
 //digitalWrite(8,LOW);
 //delay(5000);

 Serial.println("configurando a 115200Bps.."); 
 A6MODULE.begin(115200);
 
 // cambiamos la velocidad de transmisión
 delay(5000);
 Serial.println("Cambiando a 9600Bds");
 A6MODULE.println("AT+IPR=9600");
 A6MODULE.begin(9600);
 delay(5000);

 Serial.println("Módulo listo.");

// Envio de mensajes de texto
 Serial.println("Enviando AT...");
 A6MODULE.println("AT");
 delay(1000); 
 
 //Serial.println("Configurando modo texto AT+CMGF=1 "); //modo texto
 A6MODULE.println("AT+CMGF=1");
 delay(1000);

// Serial.println("Indicando de destino xxxxxx");
 A6MODULE.println("AT+CMGS=\"+3026777619\"");
 delay(3000);

//  Serial.println("Cargando mensaje");
 A6MODULE.println("hola automata");
 delay(3000);

// Serial.println("Enviando...");
 A6MODULE.println(char(26));
 delay(2000);


}

void loop() {
   while(A6MODULE.available()){
  Serial.write(A6MODULE.read());
 }

  
 while(Serial.available()){
  A6MODULE.write(Serial.read());
 }

}
