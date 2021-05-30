#include <WiFi.h>

const char* ssid = "MEGACABLE-2.4G-E9A3";
const char* password = "RtX.3080.tI";

void setup() {
  Serial.begin(115200);
  delay(10);

  //Se inicia la conexión
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  //Se verifica la conexión
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  //Lograda la conexión
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
