#include <SoftwareSerial.h>
#include <DHT.h>

#define TAP           '\t'
#define COMMA         ','

#define BAUD_RATE     9600
#define RXPIN         10
#define TXPIN         11

#define LDRPIN        A1

#define DHTPIN        2
#define DHTTYPE       DHT22

#define MODEPIN       13
#define ACTIVE        LOW
#define PASSIVE       HIGH

SoftwareSerial mySerial(RXPIN, TXPIN);
DHT dht(DHTPIN, DHTTYPE);

String strMode[] = {"active", "passive"};
String cmd = "";
uint8_t tick = 0;
uint8_t mode = 3;

void setup() {
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);
  pinMode(MODEPIN, INPUT);

  Serial.begin(BAUD_RATE);
  mySerial.begin(BAUD_RATE);

  dht.begin();
}

void loop() {

  changeMode();

  if (mode == ACTIVE) {
    while (mySerial.available()) {
      char c = mySerial.read();

      if (c != '\n') {
        cmd.concat(c);
      } else {
        Serial.print("Recieve : ");
        Serial.println(cmd);
        if (cmd == "ACT") {
          sendData();
        } else {
          mySerial.println("Invalid Command");
        }
        cmd = "";
      }
    }
  } else {
    if (tick >= 50) {
      sendData();
      tick = 0;
    }
    
    tick ++;
    delay(100);
  }
}


void changeMode() {
  int temp = digitalRead(MODEPIN);
  if (temp != mode) {
    mode = temp;
    Serial.print("Mode : ");
    Serial.println(strMode[mode]);
  }
  delay(100);
}


void sendData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float l = analogRead(LDRPIN);

  Serial.println("Sending data...");

  mySerial.print(h);
  mySerial.print(COMMA);

  mySerial.print(t);
  mySerial.print(COMMA);

  mySerial.print(l);
  mySerial.println();
}

