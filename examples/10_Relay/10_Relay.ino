#define RELAY_PIN 0

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  digitalWrite(RELAY_PIN, HIGH); // ON
  delay(2000);
  digitalWrite(RELAY_PIN, LOW);  // OFF
  delay(2000);
}
