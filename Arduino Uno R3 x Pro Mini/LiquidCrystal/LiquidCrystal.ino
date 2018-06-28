#include <LiquidCrystal.h>

#define RS  0 //RX
#define EN  1 //TX
#define D4  5
#define D5  4
#define D6  3
#define D7  2

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup()
{
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
  lcd.print("hello, world!");
  delay(1000);
  lcd.print("KUY!");
  delay(1000);
}
