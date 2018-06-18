#include <WiFi.h>
#include "DHT.h"

#define BAUD_RATE 115200

#define LDRPIN 36

#define DHTPIN 18
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();

  Serial.begin(BAUD_RATE);
  Serial.flush();

  connectToWiFi();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float l = analogRead(LDRPIN);

  String data = String(h) + ","
                + String(t) + ","
                + String(l);

  sendData(data);
  delay(500);
}

