#define TINY_GSM_MODEM_SIM7600
#include <TinyGsmClient.h>
#include <PubSubClient.h>

// Hardware Serial for SIM7600
#define MODEM_RX 17
#define MODEM_TX 16
HardwareSerial SerialGSM(1);  // UART1

// GSM / GPRS settings
const char apn[]  = "airtelgprs.com";
const char user[] = ""; // leave empty if not required
const char pass[] = ""; // leave empty if not required

// MQTT server settings
const char* mqtt_server   = "";      // IP address or domain name of the MQTT broker
const uint16_t mqtt_port  = 1883;    // Port number of the MQTT broker (default 1883 for non-TLS)
const char* mqtt_user     = "";      // Username for MQTT authentication 
const char* mqtt_password = "";      // Password for MQTT authentication 
const char* topic         = "ESP32/GSM/LED";  // MQTT topic to publish/subscribe messages


// LED pin
const int LED_PIN = 32;

// TinyGSM modem and MQTT client
#define TINY_GSM_MODEM_SIM7600
TinyGsm modem(SerialGSM);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];
  msg.trim();

  if (msg.equalsIgnoreCase("ON")) digitalWrite(LED_PIN, HIGH);
  else if (msg.equalsIgnoreCase("OFF")) digitalWrite(LED_PIN, LOW);
}

void connectMQTT() {
  while (!mqtt.connected()) {
    if (mqtt.connect("ESP32GSMClient", mqtt_user, mqtt_password)) {
      mqtt.subscribe(topic);
    } else {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  SerialGSM.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  modem.restart();
  delay(1000);

  if (!modem.gprsConnect(apn, user, pass)) {
    while (true) delay(1000);  // Stop if GPRS fails
  }

  mqtt.setServer(mqtt_server, mqtt_port);
  mqtt.setCallback(callback);

  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();
}
