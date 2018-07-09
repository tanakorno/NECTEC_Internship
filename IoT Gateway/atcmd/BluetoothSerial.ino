#include "BluetoothSerial.h"

// Bluetooth Name
#define BTNAME "ESP32-IoT-Gateway"

BluetoothSerial BTSerial;
String BTData = "";

void setupBTSerial()
{
  if (BTSerial.begin(BTNAME)) {
    Serial.println("Success to initialize Bluetooth");
  } else {
    Serial.println("Failed to initialize Bluetooth");
  }
}

void writeBTSerial(String str) {
  BTSerial.println(str);
}

void readBTSerial() {
  if (BTSerial.available()) {
    char c = BTSerial.read();

    if (c != CR and c != LF) {
      BTData.concat(c);
    }

    if (c == LF and BTData != "") {
      parseAtCmd(BTData);
      BTData = "";
    }
  }
}

