#define BUTTON_UP 35
#define BUTTON_DOWN 34
#define BUTTON_SELECT 36
#define BUTTON_BACK 39

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_BACK, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(BUTTON_UP)) Serial.println("UP pressed");
  if (!digitalRead(BUTTON_DOWN)) Serial.println("DOWN pressed");
  if (!digitalRead(BUTTON_SELECT)) Serial.println("SELECT pressed");
  if (!digitalRead(BUTTON_BACK)) Serial.println("BACK pressed");
  delay(200);
}
