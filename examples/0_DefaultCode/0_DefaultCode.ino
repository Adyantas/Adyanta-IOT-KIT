#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);   // try 0x3F if nothing shows
RTC_DS3231 rtc;

// --- Pin map ---
#define LED_PIN     32
#define BUZZER_PIN  33
#define RELAY_PIN   0
#define BTN1        34
#define BTN2        35
#define BTN3        36
#define BTN4        39

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.init();
  lcd.backlight();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(BTN4, INPUT_PULLUP);

  // --- 1. Boot screen ---
  lcd.clear();
  lcd.setCursor(5, 0); lcd.print("Adyanta");
  lcd.setCursor(5, 1); lcd.print("IOT KIT");
  delay(2000);

  // --- 2. GitHub link scrolling ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GitHub Link:");

  String link = "https://github.com/Adyantas/Adyanta-IOT-KIT";
  scrollText(link, 1, 250); // (text, row=1, scrollSpeed=250ms per step)
  lcd.clear();

  // --- 3. LED test ---
  lcd.clear(); lcd.print("LED Test (32)");
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH); delay(400);
    digitalWrite(LED_PIN, LOW);  delay(400);
  }
  delay(1000);

  // --- 4. Buzzer test ---
  lcd.clear(); lcd.print("Buzzer Test (33)");
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH); delay(300);
    digitalWrite(BUZZER_PIN, LOW);  delay(300);
  }
  delay(1000);

  // --- 5. Button test ---
  lcd.clear(); lcd.print("Button Test");
  lcd.setCursor(0, 1); lcd.print("Press any btn...");
  buttonTest();

  // --- 6. Relay test ---
  lcd.clear(); lcd.print("Relay Test (0)");
  lcd.setCursor(0, 1); lcd.print("ON");
  digitalWrite(RELAY_PIN, HIGH); delay(2000);
  lcd.setCursor(0, 1); lcd.print("OFF ");
  digitalWrite(RELAY_PIN, LOW); delay(2000);

  // --- 7. RTC test ---
  lcd.clear(); lcd.print("RTC Test...");
  delay(1000);
  if (!rtc.begin()) {
    lcd.clear(); lcd.print("RTC not found!");
    while (1);
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.printf("%02d/%02d/%04d", now.day(), now.month(), now.year());
  lcd.setCursor(0, 1);
  lcd.printf("%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  delay(1000);
}

// --- Scroll long text across a given row ---
void scrollText(String text, int row, int delayTime) {
  int len = text.length();
  if (len <= 16) {
    lcd.setCursor(0, row);
    lcd.print(text);
    delay(3000);
  } else {
    for (int i = 0; i < len - 15; i++) {
      lcd.setCursor(0, row);
      lcd.print(text.substring(i, i + 16));
      delay(delayTime);
    }
  }
}

// --- Button test helper functions ---
void buttonTest() {
  bool ledState = false;
  unsigned long lastPress = millis();
  while (true) {
    if (digitalRead(BTN1) == LOW) showButton(34, ledState);
    if (digitalRead(BTN2) == LOW) showButton(35, ledState);
    if (digitalRead(BTN3) == LOW) showButton(36, ledState);
    if (digitalRead(BTN4) == LOW) showButton(39, ledState);

    if (digitalRead(BTN1) == LOW || digitalRead(BTN2) == LOW ||
        digitalRead(BTN3) == LOW || digitalRead(BTN4) == LOW)
      lastPress = millis();

    if (millis() - lastPress > 5000) break;
  }
}

void showButton(int pin, bool &ledState) {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  lcd.clear();
  lcd.print("Button Pressed:");
  lcd.setCursor(0, 1);
  lcd.printf("GPIO %d", pin);
  delay(300);
}
