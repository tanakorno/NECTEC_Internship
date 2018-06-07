#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "SparkFunBME280.h"

#define ROW 2
#define COL 16

BME280 mySensor;
LiquidCrystal_I2C lcd(0x27, COL, ROW);

enum BMESensor {
  Humidity = 0,
  Pressure,
  Altitude,
  Temperature,
};

int curr = 0;
int prev = 3;

void setup()
{
  Serial.begin(9600);
  Serial.println("Reading basic values from BME280");

  Wire.begin();

  lcd.begin();
  lcd.backlight();

  if (mySensor.beginI2C() == false)
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while (1); //Freeze
  }

  Serial.println(mySensor.settings.I2CAddress);
}


void loop()
{
  delay(1000);
  lcd.clear();

  readSensor(curr, 0);
  readSensor(prev, 1);

  prev = curr;
  curr = (curr + 1) % 4;
}


void readSensor(int sensorNum, int line) {
  lcd.setCursor(0, line);

  switch (sensorNum) {
    case Humidity:
      lcd.print("Humid: ");
      lcd.print(mySensor.readFloatHumidity());
      break;
    case Pressure:
      lcd.print("Pressure: ");
      lcd.print(mySensor.readFloatPressure() / 100.00);
      break;
    case Altitude:
      lcd.print("Altitude: ");
      lcd.print(mySensor.readFloatAltitudeFeet());
      break;
    case Temperature:
      lcd.print("Temp(*C): ");
      lcd.print(mySensor.readTempC());
      break;
    default:
      break;
  }
}

