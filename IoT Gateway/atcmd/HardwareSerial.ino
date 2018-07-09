#include "HardwareSerial.h"

#define HWSERIAL_BR   9600

#define RXPIN         18
#define TXPIN         19

HardwareSerial HWSerial(1);
String HWData = "";

void setupHWSerial() {
  HWSerial.begin(HWSERIAL_BR, SERIAL_8N1, RXPIN, TXPIN);
}

void writeHWSerial(String str) {
  HWSerial.println(str);
} 

void readHWSerial() {
  if (HWSerial.available()) {
    char c = HWSerial.read();

    if (c != CR and c != LF) {
      HWData.concat(c);
    }

    if (c == LF and HWData != "") {
      if (HWData != "invalid command") {
        CMDSerial.print("get data from sensor: ");
        CMDSerial.println(HWData);
        if (actCloud) {
          sendData(HWData);
        }
      }
      HWData = "";
    }
  }
}


