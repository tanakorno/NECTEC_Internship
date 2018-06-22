#include "EEPROM.h"

#define SSID_ADDR     0
#define PASS_ADDR     32

#define SSID_SIZE     31
#define PASS_SIZE     31

#define EEPROM_SIZE   64


String getSsid() {
  return readEEPROM(SSID_ADDR, SSID_SIZE);
}
void setSsid(String ssid) {
  writeEEPROM(SSID_ADDR, ssid);
}

String getPass() {
  return readEEPROM(PASS_ADDR, PASS_SIZE);
}
void setPass(String pass) {
  writeEEPROM(PASS_ADDR, pass);
}

void setAP(String ssid, String pass) {
  if (ssid.length() > SSID_SIZE) {
    CMDSerial.print("ssid length is too long (max ");
    CMDSerial.print(SSID_SIZE);
    CMDSerial.println(" characters)");
  } else if (pass.length() > PASS_SIZE) {
    CMDSerial.print("password length is too long (max ");
    CMDSerial.print(PASS_SIZE);
    CMDSerial.println(" characters)");
  } else {
    CMDSerial.print("set ssid: "); CMDSerial.println(ssid);
    setSsid(ssid);
    CMDSerial.print("set password: "); CMDSerial.println(pass);
    setPass(pass);
    //CMDSerial.println(OK);
  }
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
  uint8_t i = 0;
  for (i = 0; i < str.length(); i++) {
    EEPROM.write(_start + i, str[i]);
  }

  EEPROM.write(_start + i, EOS);
  EEPROM.commit();
}

String readEEPROM(int _start, int _stop)
{
  String str = "";
  for (uint8_t i = 0; i < _stop; i++) {
    char c = EEPROM.read(_start + i);
    if (c == EOS) break;
    str.concat(c);
  }
  return str;
}
