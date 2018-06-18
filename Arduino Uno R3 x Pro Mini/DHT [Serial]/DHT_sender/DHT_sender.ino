#include <SoftwareSerial.h>
#include "DHT.h"

#define TAP "\t"
#define LDRPIN A3
#define DHTPIN 2
#define DHTTYPE DHT22

#define RXPIN 10
#define TXPIN 11

SoftwareSerial mySerial(RXPIN, TXPIN);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);

  mySerial.begin(9600);
  Serial.begin(9600);
  dht.begin();

  Serial.println("DHT22 Sensor Test!");
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //  float f = dht.readTemperature(true); // isFahrebheit = true
  float l = analogRead(LDRPIN);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%");
  Serial.print(TAP);

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(TAP);

  Serial.print("LDR: ");
  Serial.print(l);

  Serial.println();

  // Sending Data

  mySerial.print("Humidity: ");
  mySerial.print(h);
  mySerial.print("%");
  mySerial.print(TAP);

  mySerial.print("Temperature: ");
  mySerial.print(t);
  mySerial.print(TAP);

  mySerial.print("LDR: ");
  mySerial.print(l);

  mySerial.println();
}

