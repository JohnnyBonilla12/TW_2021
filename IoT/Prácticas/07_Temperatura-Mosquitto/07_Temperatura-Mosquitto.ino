#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

#define DHTpin 15

const char* ssid = "MEGACABLE-2.4G-E9A3";
const char* password = "RtX.3080.tI";
const char* mqtt_server = "192.168.100.9";

uint8_t BUILTIN_LED = 2;

float temperatura;
DHTesp dht;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (100)
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  dht.setup(DHTpin, DHTesp::DHT11);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    /* Linea donde se envia el Usuario y Contraseña
    if (client.connect(clientId.c_str(), "johnny", "admin")) {*/
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("temperaturas", "#Johnny B. ESP32 comming online#");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  delay(dht.getMinimumSamplingPeriod());

  unsigned long now = millis();
  if (now - lastMsg > 4000) {
    lastMsg = now;
    temperatura = dht.getTemperature();
    snprintf (msg, MSG_BUFFER_SIZE, "|JB| |Xalapa, Unidad y Progreso|: °C %.2f", temperatura);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("temperaturas", msg);
  }
}
