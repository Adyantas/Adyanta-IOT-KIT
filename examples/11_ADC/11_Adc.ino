#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <LiquidCrystal_I2C.h>

Adafruit_ADS1115 ads;
LiquidCrystal_I2C lcd(0x27, 16, 2);   // try 0x3F if nothing shows

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA=21, SCL=22
  delay(1000);

  lcd.init();
  lcd.backlight();

  Serial.println("ESP32 + ADS1115 I2C ADC Test");

  if (!ads.begin()) {
    Serial.println("Failed to find ADS1115 chip");
    lcd.clear();
    lcd.print("ADS1115 Error!");
    while (1);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ADS1115 Ready");
  delay(2000);
}

void loop() {
  // Read all 4 channels
  int16_t adc0 = ads.readADC_SingleEnded(0);
  int16_t adc1 = ads.readADC_SingleEnded(1);
  int16_t adc2 = ads.readADC_SingleEnded(2);
  int16_t adc3 = ads.readADC_SingleEnded(3);

  // Convert to voltage (default gain ±6.144V => 1 bit = 0.1875mV)
  float voltage0 = adc0 * 0.1875 / 1000.0;
  float voltage1 = adc1 * 0.1875 / 1000.0;
  float voltage2 = adc2 * 0.1875 / 1000.0;
  float voltage3 = adc3 * 0.1875 / 1000.0;

  // Print to Serial Monitor
  Serial.printf("ADC0: %6d  V: %.4f\n", adc0, voltage0);
  Serial.printf("ADC1: %6d  V: %.4f\n", adc1, voltage1);
  Serial.printf("ADC2: %6d  V: %.4f\n", adc2, voltage2);
  Serial.printf("ADC3: %6d  V: %.4f\n\n", adc3, voltage3);

  // Display 2 channels per screen (auto scroll)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A0:"); lcd.print(voltage0, 2); lcd.print("V ");
  lcd.print("A1:"); lcd.print(voltage1, 2); lcd.print("V");

  lcd.setCursor(0, 1);
  lcd.print("A2:"); lcd.print(voltage2, 2); lcd.print("V ");
  lcd.print("A3:"); lcd.print(voltage3, 2); lcd.print("V");

  delay(1000);
}
