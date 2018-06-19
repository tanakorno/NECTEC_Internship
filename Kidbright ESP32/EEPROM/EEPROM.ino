#include <EEPROM.h>

#define BAUD_RATE 9600

void setup()
{
    Serial.begin(BAUD_RATE);
    Serial.println(EEPROM.read(256));
}

void loop()
{

}