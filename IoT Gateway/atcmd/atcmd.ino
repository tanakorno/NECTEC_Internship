// main

#define CR          '\r'
#define LF          '\n'
#define EOS         '\0'

#define ESP32_BR    115200
#define CMDSerial   BTSerial

void setup()
{
  Serial.begin(ESP32_BR);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  setupEEPROM();
  setupHWSerial();
  setupBTSerial();
}


void loop()
{
  readHWSerial(); // Sensor
  readBTSerial(); // User
}

