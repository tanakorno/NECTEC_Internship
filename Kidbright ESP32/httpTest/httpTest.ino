#include <WiFi.h>
#include <HTTPClient.h>

#define BAUD_RATE 115200

#define LEDSTAT 2
#define LDRPIN 36

#define CLOUD_URL String("http://push02.igridproject.info/kb01?data=")

char* ssid = "BS-IOT";
char* password = "1234567890";

void setup()
{
  pinMode(LEDSTAT, OUTPUT);
  Serial.begin(BAUD_RATE);

  connectToWiFi(ssid, password);
}

void loop()
{
  String strldr = String(analogRead(LDRPIN));
  sendData(CLOUD_URL + strldr);
}


void connectToWiFi(char* ssid, char* password) {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

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
