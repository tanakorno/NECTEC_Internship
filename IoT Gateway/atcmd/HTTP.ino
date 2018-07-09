#include "HTTPClient.h"

#define LEDSTAT 2
//#define cloud_url "http://push02.igridproject.info/kb01?data="

void sendData(String data)
{
  String url = getCloud() + data;

  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi(getSsid(), getPass());
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);

    CMDSerial.print("sending: ");
    CMDSerial.println(data);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      CMDSerial.print("recieve: ");
      CMDSerial.println(payload);
      //sendingBlink();
    } else {
      delay(5000);
    }
    http.end();
  } else {
    printNoWiFi();
  }
}

void sendingBlink()
{
  digitalWrite(LEDSTAT, LOW);
  delay(100);
  digitalWrite(LEDSTAT, HIGH);
  delay(1900);
}


