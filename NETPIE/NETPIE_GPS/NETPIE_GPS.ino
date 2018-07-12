#include "WiFi.h"
#include "MicroGear.h"
#include "HardwareSerial.h"
#include "TinyGPS++.h"

const char* ssid     = "iPhone";
const char* password = "040466723";

#define APPID   "PhinxTest"
#define KEY     "4l4HTEeHuS4Pe3B"
#define SECRET  "PptXcPP66PnR6GkRZdM0hi02A"
#define ALIAS   "esp32-KidBright"

#define SERIAL_BR     115200
#define HWSERIAL_BR   9600
#define RXPIN         18
#define TXPIN         19

WiFiClient client;
MicroGear microgear(client);

HardwareSerial HWSerial(1);
TinyGPSPlus gps;

int timer = 0;

void setup() {
  microgear.on(MESSAGE, onMsghandler);
  microgear.on(PRESENT, onFoundgear);
  microgear.on(ABSENT, onLostgear);
  microgear.on(CONNECTED, onConnected);

  Serial.begin(SERIAL_BR);
  Serial.println("Starting...");

  HWSerial.begin(HWSERIAL_BR, SERIAL_8N1, RXPIN, TXPIN);
  
  setupWiFi();

  microgear.init(KEY, SECRET, ALIAS);
  microgear.connect(APPID);
}


void loop() {
  if (microgear.connected()) {
    microgear.loop();

    if (timer >= 2000) {
      // ***
      microgear.chat(ALIAS, getGPSData());
      // ***
      timer = 0;
    } else {
      timer += 100;
    }

  } else {
    Serial.println("connection lost, reconnect...");

    if (timer >= 5000) {
      setupWiFi();
      microgear.connect(APPID);
      timer = 0;
    } else {
      timer += 100;
    }
  }

  delay(100);
}

void setupWiFi() {
  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

String getGPSData() {
  while (HWSerial.available()) {
    char c = HWSerial.read();
    gps.encode(c);
  }

  String val = String(gps.satellites.value()) + ","
             + String(gps.location.lat()) + ","
             + String(gps.location.lng());
               
  return val;
}

// microgear built-in
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  msg[msglen] = '\0';
  Serial.println((char *)msg);
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Found new member --> ");
  for (int i = 0; i < msglen; i++)
    Serial.print((char)msg[i]);
  Serial.println();
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Lost member --> ");
  for (int i = 0; i < msglen; i++)
    Serial.print((char)msg[i]);
  Serial.println();
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  microgear.setName(ALIAS);
}
