#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Try 0x3F if 0x27 doesn't work

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  if (!rtc.begin()) {
    Serial.println("RTC not found!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RTC not found!");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  lcd.setCursor(2, 0);
  lcd.print("RTC Initialized");
  delay(2000);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  // Print to Serial (optional)
  Serial.printf("%02d:%02d:%02d %02d/%02d/%04d\n",
                now.hour(), now.minute(), now.second(),
                now.day(), now.month(), now.year());

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.printf("%02d:%02d:%02d", now.hour(), now.minute(), now.second());

  lcd.setCursor(0, 1);
  lcd.printf("%02d/%02d/%04d", now.day(), now.month(), now.year());

  delay(1000);
}
