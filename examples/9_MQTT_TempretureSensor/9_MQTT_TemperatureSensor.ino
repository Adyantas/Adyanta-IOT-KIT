#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Wi-Fi / MQTT
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPass";
const char* mqtt_server = "192.168.1.100"; // replace with your server IP
const char* topic_temp = "adyanta/temperature";
const char* topic_humi = "adyanta/humidity";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Connected");

  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (!isnan(t)) client.publish(topic_temp, String(t, 1).c_str());
  if (!isnan(h)) client.publish(topic_humi, String(h, 1).c_str());

  Serial.printf("Temp: %.1f °C  Humi: %.1f %%\n", t, h);

  delay(2000);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_DHT")) {
      Serial.println("MQTT connected");
    } else {
      delay(1000);
    }
  }
}
