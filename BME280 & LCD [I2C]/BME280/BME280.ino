#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "SparkFunBME280.h"

#define ROW 2
#define COL 16

BME280 mySensor;
LiquidCrystal_I2C lcd(0x27, COL, ROW);

void setup()
{
  Serial.begin(9600);
  Serial.println("Reading basic values from BME280");

  Wire.begin();

  if (mySensor.beginI2C() == false)
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while (1); //Freeze
  }

  Serial.println(mySensor.settings.I2CAddress);

  // LCD
  lcd.begin();
  lcd.backlight();
}

void loop()
{
  float humidity = mySensor.readFloatHumidity();
  float pressure = mySensor.readFloatPressure();
  float altitude = mySensor.readFloatAltitudeFeet();
  float temp = mySensor.readTempC();

  doPrint("Humidity: ", humidity);
  doPrint("Pressure: ", pressure);
  doPrint("Altitude: ", altitude);
  doPrint("Temperature: ", temp);
}

void doPrint(String str, float val) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(str);
  lcd.setCursor(0, 1);
  lcd.print(val);
  delay(1000);
}

