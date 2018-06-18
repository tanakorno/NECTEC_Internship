#include <HTTPClient.h>

#define LEDSTAT 2
#define cloud_url "http://push02.igridproject.info/kb01?data="

void sendData(String data)
{
  String url = cloud_url + data;

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);

    Serial.println();
    Serial.print("Sending: ");
    Serial.println(data);

    int httpCode = http.GET();
    
    if (httpCode > 0) {

      String payload = http.getString();
      Serial.print("Recieve: ");
      Serial.println(payload);
      sendingBlink();

    } else {
      delay(5000);
    }

    http.end();
  } else {
    reconnectToWiFi();
  }
}


void sendingBlink()
{
  digitalWrite(LEDSTAT, LOW);
  delay(100);
  digitalWrite(LEDSTAT, HIGH);
  delay(1900);
}
