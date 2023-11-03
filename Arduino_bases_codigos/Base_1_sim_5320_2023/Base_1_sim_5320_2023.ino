#include <SoftwareSerial.h>

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

}

void loop() {
  if (Serial1.available())
  {
    Serial.write(Serial.read());
  }

  if(Serial1.available())
  {
    while(Serial.available())
    {
      Serial.write(Serial.read());
    }
    Serial1.println();
  } 

}
