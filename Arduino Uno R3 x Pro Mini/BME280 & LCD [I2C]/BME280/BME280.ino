#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "SparkFunBME280.h"

#define BAUD_RATE 9600

#define ROW 2
#define COL 16

BME280 mySensor;
LiquidCrystal_I2C lcd(0x27, COL, ROW);

void setup()
{
  Wire.begin();
//  Serial.begin(BAUD_RATE);
//  Serial.println("Reading basic values from BME280");

  if (mySensor.beginI2C() == false)
  {
    lcd.println("The sensor did not respond. Please check wiring.");
    while (1); //Freeze
  }

//  Serial.println(mySensor.settings.I2CAddress);

  // LCD
  lcd.begin();
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

