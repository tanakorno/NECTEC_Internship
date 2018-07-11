#include "EEPROM.h"

#define SSID_ADDR     0
#define PASS_ADDR     33
#define CLOUD_ADDR    66

#define SSID_SIZE     32
#define PASS_SIZE     32
#define CLOUD_SIZE    64

#define EEPROM_SIZE   1024

String getSsid() {
  return readEEPROM(SSID_ADDR, SSID_SIZE);
}
void setSsid(String ssid) {
  if (ssid.length() > SSID_SIZE) {
    CMDSerial.print("ssid length is too long (max ");
    CMDSerial.print(SSID_SIZE);
    CMDSerial.println(" characters)");
  } else {
    CMDSerial.print("set ssid: ");
    CMDSerial.println(ssid);
    writeEEPROM(SSID_ADDR, ssid);
  }
}

String getPass() {
  return readEEPROM(PASS_ADDR, PASS_SIZE);
}
void setPass(String pass) {
  if (pass.length() > PASS_SIZE) {
    CMDSerial.print("password length is too long (max ");
    CMDSerial.print(PASS_SIZE);
    CMDSerial.println(" characters)");
  } else {
    CMDSerial.print("set password: ");
    CMDSerial.println(pass);
    writeEEPROM(PASS_ADDR, pass);
  }
}

String getCloud() {
  return readEEPROM(CLOUD_ADDR, CLOUD_SIZE);
}
void setCloud(String url) {
  if (url.length() > CLOUD_SIZE) {
    CMDSerial.print("cloud url length is too long (max ");
    CMDSerial.print(CLOUD_SIZE);
    CMDSerial.println(" characters)");
  } else {
    CMDSerial.print("set cloud url: ");
    CMDSerial.println(url);
    writeEEPROM(CLOUD_ADDR, url);
  }
}

void setAP(String ssid, String pass) {
  setSsid(ssid);
  setPass(pass);
}

void setupEEPROM()
{
  if (EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Success to initialize EEPROM");
  } else {
    Serial.println("Failed to initialize EEPROM");
  }
}

void writeEEPROM(int _start, String str)
{
  int i = 0;
  for (i = 0; i < str.length(); i++) {
    EEPROM.write(_start + i, str[i]);
  }

  EEPROM.write(_start + i, EOS);
  EEPROM.commit();
}

String readEEPROM(int _start, int _stop)
{
  String str = "";
  for (int i = 0; i < _stop; i++) {
    char c = EEPROM.read(_start + i);
    if (c == EOS) break;
    str.concat(c);
  }
  return str;
}

