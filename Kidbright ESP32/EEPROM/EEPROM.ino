#include "EEPROM.h"

#define CR            '\r'
#define LF            '\n'
#define EOS           '\0'

#define ESP32_BR      115200
#define EEPROM_SIZE   64 // max 1024
#define ID_ADDR       0

String data = "";

void setup()
{
  Serial.begin(ESP32_BR);
  Serial.println("Start...");
  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
}

void loop()
{
  if (Serial.available()) {
    char c = Serial.read();
    if (c != CR and c != LF) {
      data.concat(c);
    }
    if (c == LF) {
      write(ID_ADDR, data);
      read();
      data = "";
    }
  }
  delay(100);
}

void read()
{
  Serial.print("Reading : ");
  for (int i = 0; i < EEPROM_SIZE; i++) {
    int val = EEPROM.read(i);
    if (val == EOS) break;
    Serial.print(char(val));
  }
  Serial.println("");
}

void write(int addr, String str)
{
  int N = str.length();
  Serial.print("Writing : "); Serial.println(str);
  for (int i = 0; i < N; i++) {
    EEPROM.write(addr + i, str[i]);
  }
  EEPROM.write(addr + N, EOS);
  EEPROM.commit();
}
