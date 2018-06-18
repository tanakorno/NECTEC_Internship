#include <HardwareSerial.h>

#define LF          '\n'
#define CR          '\r'
#define ESP32_BR    115200
#define SERIAL_BR   9600

#define RXPIN 18
#define TXPIN 19

HardwareSerial mySerial(1);
String data = "";

void setup() {
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);

  Serial.begin(ESP32_BR);
  mySerial.begin(SERIAL_BR, SERIAL_8N1, RXPIN, TXPIN);

  connectToWiFi();
}

void loop() {
  if (mySerial.available()) {
    char c = mySerial.read();

    // Serial.print(int(c));

    if (c != CR and c != LF) {
      data.concat(c);
    }

    if (c == LF) {
      if (data != "Invalid Command") {
        sendData(data);
        data = "";
      }
    }
    
  }

  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

