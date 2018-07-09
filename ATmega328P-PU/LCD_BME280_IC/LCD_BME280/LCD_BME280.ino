#include "Wire.h"

#include "LiquidCrystal.h"
#include "SparkFunBME280.h"

BME280 mySensor;
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

void setup() {
  Wire.begin();
  lcd.begin(16, 2);

  mySensor.setI2CAddress(0x76);
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    lcd.print("EER");
    delay(5000); //Freeze
  }
}

void loop() {
  delay(1000);

  float pressure = mySensor.readFloatPressure();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Preasure : ");
  lcd.setCursor(0, 1);
  lcd.print(pressure);
  lcd.print(" Pa");
}
