#include <HTTPClient.h>

void sendData(String url)
{
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);

    Serial.println();
    Serial.print("Sending: ");
    Serial.println(url);
    
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
    
    Serial.println();
    Serial.print("Re-");
    connectToWiFi(ssid, password);
    delay(5000);
  }
}


void sendingBlink()
{
  digitalWrite(LEDSTAT, LOW);
  delay(100);
  digitalWrite(LEDSTAT, HIGH);
  delay(1900);
}
