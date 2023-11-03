// Ejemplo de prueba para el modulo RTC_DS3231
// Escrito ORIGINAL por JeeLabs, public domain
// Traducido por Konrad Peschka @konredus

#include <RTClib.h>

RTC_DS3231 modulo_rtc;

//este vector que contiene los nombres de la semana
char DiasDeLaSemana[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

void setup () {
  Serial.begin(9600);

  //este if chequea si el modulo_rtc inicio de forma correcta
  if (! modulo_rtc.begin()) {
    Serial.println("No pudimos encontrar ningun RTC");
    Serial.flush();
    abort();
  }

  // La primera vez o cuando hayamos cambiado la bateria del RTC
  //seguramente necesitemos configurarlo a la fecha y el horario actual
  //Para esas ocasiones tendremos que descomentar las 2 lineas de codigo
  //que estan aqui abajo y colocar la fecha + la hora que queremos que tenga

  //modulo_rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //modulo_rtc.adjust(DateTime(2023, 10, 15, 1, 45, 0));

  //luego cuando hayamos cargado este codigo, los volvemos a comentar
  //y recargamos el codigo a nuestro Arduino para que no lo vuelva a pisar
  //cada vez qeu se reinicia la placa Arduino.
}

void loop () {
  //con "now" lo qeu hace esuna especie de SUB-variable
  //donde guarda toda la info que llega del modulo
  DateTime ahora = modulo_rtc.now();

  //una vez que leimos el sensor, ya todo queda guardado
  //en la variable "ahora", para leer los SUB-campos de "ahora"
  //usamos el "punto" y colocamos "año", "mes", "dia","hora"
  //"minuto", "segundo", todo en ingles.
  Serial.print(ahora.year());
  Serial.print('/');
  Serial.print(ahora.month());
  Serial.print('/');
  Serial.print(ahora.day());
  Serial.print(" (");
  Serial.print(DiasDeLaSemana[ahora.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(ahora.hour());
  Serial.print(':');
  Serial.print(ahora.minute());
  Serial.print(':');
  Serial.print(ahora.second());
  Serial.println();

  //La diferencia del DS3231 con con respecto al DS1307
  //Es que este viene con un sensor de temperatura en el modulo
  Serial.print("Temperatura: ");
  Serial.print(modulo_rtc.getTemperature());
  Serial.println(" *C");

  Serial.println();
  delay(1000);
}
