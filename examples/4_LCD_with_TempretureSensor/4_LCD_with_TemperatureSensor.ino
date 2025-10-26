#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 27
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);   // use 0x3F if 0x27 doesn't work

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("Adyanta IOT KIT");
  lcd.setCursor(2, 1);
  lcd.print("DHT11 Sensor");
  delay(2000);
  lcd.clear();
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Sensor error!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT11 Error!");
  } else {
    Serial.print("Temp: ");
    Serial.print(t);
    Serial.print("°C  Humidity: ");
    Serial.print(h);
    Serial.println("%");

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t, 1);
    lcd.print((char)223); // degree symbol
    lcd.print("C   ");

    lcd.setCursor(0, 1);
    lcd.print("Humi: ");
    lcd.print(h, 1);
    lcd.print("%    ");
  }

  delay(2000);
}
