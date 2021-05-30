#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <BlynkSimpleEsp32.h>

const char* ssid = "MEGACABLE-2.4G-E9A3";
const char* pass = "RtX.3080.tI";
const char* mqtt_server = "192.168.100.9";
const char* auth = "I5rDyFOFl7F0JFEW-wwKW4khUKITmMBk";
 
#define MQ2 34

uint8_t BUILTIN_LED = 2;
int sensorValue = 0;
boolean state = false;

BlynkTimer timer;
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (100)
char msg[MSG_BUFFER_SIZE];

//Apartado de conexión a la Red Inalámbrica
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

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

//Apartado de acciones al momento de recibir un mensaje del topico al que nos suscribimos
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, HIGH);
  } else {
    digitalWrite(BUILTIN_LED, LOW);
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
      //client.publish("monitor", "#Johnny B. ESP32 comming online#");
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
  //Debug console
  Serial.begin(115200);
  pinMode(MQ2, INPUT);
  pinMode(BUILTIN_LED, OUTPUT); 

  setup_wifi();
  Blynk.begin(auth, ssid, pass);
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  timer.setInterval(1000L, sendUptime);
}
 
void sendUptime() {
  sensorValue = analogRead(MQ2);
  Blynk.virtualWrite(V1, sensorValue);
  Serial.println(sensorValue);

  if(sensorValue > 600){
    Blynk.notify("Gas Detected!");
    digitalWrite(BUILTIN_LED, HIGH);
    
    snprintf (msg, MSG_BUFFER_SIZE, "{\"gas\":%ld", sensorValue);
    strcat(msg, ",\"lat\":19.552636,\"lon\":-96.950224,\"esp\":\"JBL\"}");
    
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("gas", msg);

    //delay(15000);
  } else{
    digitalWrite(BUILTIN_LED, LOW);
  }
}
 
void loop() {
  Blynk.run();
  timer.run();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
