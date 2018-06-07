#include <SoftwareSerial.h>

#define BR 9600
#define RXPIN 0
#define TXPIN 1

SoftwareSerial mySerial(RXPIN, TXPIN);
String data = "";

void setup()
{
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);

  Serial.begin(BR);
  mySerial.begin(BR);
}

void loop()
{
  while (mySerial.available())
  {
    char character = mySerial.read();
    data.concat(character);
    if (character == '\n')
    {
      Serial.print("Received: ");
      Serial.print(data);

      data = "";
    }
  }
}
