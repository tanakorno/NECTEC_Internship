#include "SoftwareSerial.h" // Uno R3
#include "TinyGPS++.h"

#define RXPIN       3
#define TXPIN       4

#define GPS_BR      9600

SoftwareSerial SWSerial(RXPIN, TXPIN);
TinyGPSPlus myGPS;

int getSat() { return myGPS.satellites.value(); }
float getLat() { return myGPS.location.lat(); }
float getLng() { return myGPS.location.lng(); }

void setupGPS() {
  SWSerial.begin(GPS_BR);
}

void readData() {
  if (millis() > 5000 && myGPS.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
  }
  
  while (SWSerial.available()) {
    char c = SWSerial.read();
    myGPS.encode(c);
  }
}
