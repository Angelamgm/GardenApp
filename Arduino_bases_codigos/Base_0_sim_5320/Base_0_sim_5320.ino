#include <SoftwareSerial.h>
//#include <TinyGPS.h>

SoftwareSerial gsm(7,8);

char numero_cel[]="3105042211";
int estado=13;
int led = 12;
int i=0;
int j=0;
char DAT;
char DAT_dos;
char datosSERIAL[10];
//char DAT_GPS;
float flat, flon;

char clave_uno[]={ 'L' , 'E' , 'D' , 'O' , 'N' };   //Aqui cambiamos todo el mensaje de control
//char clave_uno[]={ 'L' , 'E' , 'D' , 'O' , 'F' }; //Aqui cambiamos todo el mensaje de control



void setup() {
  pinMode(led,OUTPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  gsm.begin(9600);
  Serial.println("Sistema Garden app");
  delay(500);
  configuracionInicial();
}

void loop() {
  
  Serial.println("esperando recibir mensaje...");
  while(true)
  {
    leer_mensaje();
  }

}


void configuracionInicial()
{
  Serial.print("Configurando ... espere");
  delay(2000);
  gsm.println("AT+IPR=9600");
  Serial.println("AT+IPR=9600");
  delay(100);
  gsm.println("AT+CMGF=1");            // MODO TEXTO
  Serial.println("AT+CMGF=1");         // MODO TEXTO
  delay(100);
  gsm.println("AT+CMGR=?");            // ACTIVAMOS CODIGO PARA RECIBIR MENSAJES
  Serial.println("AT+CMGR=?");         // ACTIVAMOS CODIGO PARA RECIBIR MENSAJES
  delay(100);
  gsm.println("AT+CNMI=2,2,0,0 ");    //ACTIVAMOS PARA VER MENSAJES
  delay(100);
  Serial.println("AT+CNMI=2,2,0,0 "); //ACTIVAMOS PARA VER MENSAJES
  delay(100);
  Serial.println("configuracion terminada");
  delay(2000);
  
}

void leer_mensaje()
{
  salir:
  if (gsm.available()>0)
  {
    char DAT = gsm.read();
    if(DAT=='@')                     //El arroba hace detectar el inicio del código
    {
      digitalWrite(estado,HIGH);     //Led de testeo de mensaje
      Serial.println("----llego dato----");  //Para verificar si lo detecto
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      while(true)                   //Ingresa en un while para leer solo los códigos futuros que están por llegar después de la 
      {
            if(gsm.available()>0)
            {
              char DAT_datos = gsm.read(); //@LEDON enter
              datosSERIAL[j] =DAT_dos;     //Almacena en cadena de caracteres, suma de caracteres
              j++;
              //////////////////////////
              if( DAT_dos == '\n' )   //Cuando termine de enviar los datos dará un enter
              {
                Serial.print(" ++++++++ Verificando codigo y accion a realizar +++++++"); //Imprime los caracteres almacenados para
                Serial.print(" Mensaje que LLEGO!!! ");
                    for( int i = 0 ; i <= j ; i++ )
                    {
                        Serial.print(datosSERIAL[i]);  //Imprime todo el codigo guardado en el array
                    }
                    led_on();        //Llama a la función y verifica código
                    //led_off();       //Llama a la función para ver si es de apagar el led
                    //gps_on();       //Verifica si es código de activación de gps
                    error_de_codigo();
                    delay(10);
                    digitalWrite(estado, LOW); // Apaga el led después de verificar

                     for( int i = 0; i < j; i++ )
                     {
                        datosSERIAL[i] == 0; //Borro array
                        DAT_dos = 0;
                        DAT=0;
                        
                     }
               j=0;         //Borra el puntero o acumulador si no se hace esto no detecta los sigiuentes códigos
               goto salir;  //Sale de todos los ciclos y va al inicio para volver a leer el código      
              }// cierra al \n

              ///////////////////////////
            }//cierre del segundo if
      }//while
    }//arroba
  }//serial available
}


void led_on ()
{
  if(datosSERIAL[0]==clave_uno[0] && datosSERIAL[1]==clave_uno[1] && datosSERIAL[2]==clave_uno[2] && datosSERIAL[3]==clave_uno[3] && datosSERIAL[4]==clave_uno[4]  )
  {
    digitalWrite(led,HIGH);
    Serial.println("LED ACTIVADO....");
    mensaje_encendido(); // Envia mensajes al celular
    
  }
  else Serial.println("Codigo incorrecto led on");
  
}



void mensaje_encendido()
{
  gsm.print("AT+CMGF=1"); // MODO TEXTO
  // Imprime los datos al puerto serie como texto ASCCI seguido de un retorno de carro
  delay(1000);
  gsm.print("AT+CMGS="); // Comando de envio de mensaje a un numero determinado
  delay(1000);
  //Imprime los datos al puerto serie como texto ASCII
  gsm.print((char)34); //Ponemos las commilas ", para que los tome debe ser char de lo contrario el serial en
  gsm.print(numero_cel); // Colocamos numero de telefoco
  gsm.print((char)34); //Volvemos a poner el caracter "
  delay(1000);
  gsm.println("led encendido"); //mensaje que enviare
  gsm.print((char)26); //ponemos el simbolo ascii 26, que corresponde a CTRL + Z, con lo que el modulo sabe que

  Serial.println("led encendido"); //Mensaje que enviare
}

void error_de_codigo()
{
  if(datosSERIAL[0]==clave_uno[0] && datosSERIAL[1]==clave_uno[1] && datosSERIAL[2]==clave_uno[2] && datosSERIAL[3]==clave_uno[3] && datosSERIAL[4]==clave_uno[4]  )
  {
    Serial.println("Codigo enviado correcto");
  }
  else
  {
    Serial.println("Codigo enviado INcorrecto");
  }
}
