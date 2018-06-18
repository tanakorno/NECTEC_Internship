#include <HardwareSerial.h>

#define ESP32_BR 115200
#define SERIAL_BR 9600

#define RXPIN 18
#define TXPIN 19

HardwareSerial mySerial(1);

void setup() {
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);

  Serial.begin(ESP32_BR);
  mySerial.begin(SERIAL_BR, SERIAL_8N1, RXPIN, TXPIN);
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

