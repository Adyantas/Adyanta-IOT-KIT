#include <WiFi.h>
#include <PubSubClient.h>

#define LED_PIN 32

// Wi-Fi credentials
const char* ssid = "YourWiFi";
const char* password = "YourPass";

// Local MQTT Broker IP
const char* mqtt_server = "192.168.1.100"; // replace with your server IP
const char* topic = "adyanta/led";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Connected");

  client.setServer(mqtt_server, 1883);
  client.setCallback(mqttCallback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) msg += (char)payload[i];
  Serial.print("Message: "); Serial.println(msg);

  if (msg == "ON") digitalWrite(LED_PIN, HIGH);
  if (msg == "OFF") digitalWrite(LED_PIN, LOW);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32_WiFi_LED")) {
      client.subscribe(topic);
      Serial.println("Subscribed to LED topic");
    } else {
      delay(1000);
    }
  }
}
