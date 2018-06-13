#include <SoftwareSerial.h>

#define BAUD_RATE 9600

#define RXPIN 10
#define TXPIN 11

SoftwareSerial mySerial(RXPIN, TXPIN);

void setup() {
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);

  Serial.begin(BAUD_RATE);
  mySerial.begin(BAUD_RATE);
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

