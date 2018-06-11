#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define BAUD_RATE 115200

#define LEDSTAT 2
#define LDRPIN 36

#define DHTPIN 18
#define DHTTYPE DHT22

#define cloud_url "http://push02.igridproject.info/kb01?data="

char* ssid = "BS-IOT";
char* password = "1234567890";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  dht.begin();
  
  Serial.begin(BAUD_RATE);
  Serial.flush();
  
  connectToWiFi(ssid, password);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float l = analogRead(LDRPIN);

  String data = String(h) + ","
              + String(t) + ","
              + String(l);

  sendData(cloud_url + data);
  
  delay(500);
}

