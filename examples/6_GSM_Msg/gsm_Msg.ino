#define MODEM_RX 17   // ESP32 RX2  <-  SIM7600 TX
#define MODEM_TX 16   // ESP32 TX2  ->  SIM7600 RX

HardwareSerial gsm(1);  // Use UART1 (Serial1)

void setup() {
  Serial.begin(115200);     // Serial monitor
  gsm.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);  // SIM7600

  Serial.println("SIM7600 GSM Test Started");
  delay(3000);

  // Basic check
  sendCommand("AT");
  delay(1000);

}

void loop() {
  // Forward data from GSM -> Serial
  while (gsm.available()) {
    Serial.write(gsm.read());
  }

  // Forward data from Serial -> GSM
  while (Serial.available()) {
    gsm.write(Serial.read());
  }
}


void sendCommand(const char* cmd) {
  Serial.print("Sending: ");
  Serial.println(cmd);
  gsm.println(cmd);
}