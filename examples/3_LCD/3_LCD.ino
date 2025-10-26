#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // check address 0x27 or 0x3F

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello ESP32");
  lcd.setCursor(0, 1);
  lcd.print("LCD Working");
}

void loop() {
}
