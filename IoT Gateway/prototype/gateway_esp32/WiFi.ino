#include <WiFi.h>

char* ssid = "BS-IOT";
char* password = "1234567890";

void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnectToWiFi() {
  Serial.println();
  Serial.print("Re-");
  connectToWiFi();
}


