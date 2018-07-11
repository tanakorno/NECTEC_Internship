// main

#define CR          '\r'
#define LF          '\n'
#define EOS         '\0'

#define ESP32_BR    115200
#define CMDSerial   BTSerial

void setup()
{
  Serial.begin(ESP32_BR);

  setupEEPROM();
  setupHWSerial();
  setupBTSerial();
}


void loop()
{
  readHWSerial(); // Sensor
  readBTSerial(); // User
}

