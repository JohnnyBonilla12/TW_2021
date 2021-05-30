#include <WiFi.h>
#include <WebServer.h>
#include "DHTesp.h"

#define DHTpin 15

const char* ssid = "MEGACABLE-2.4G-E9A3";
const char* password = "RtX.3080.tI";

float temperatura;
float humedad;

DHTesp dht;
WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  dht.setup(DHTpin, DHTesp::DHT11);

  // Verificar estado de la conexión
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("IP: ");  
  Serial.println(WiFi.localIP());
  
  
  server.on("/", controlarIndex);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Estado\tHumedad (%)\tTemperatura (C)\t(F)\tIndiceCalor (C)\t(F)");
}
void loop() {
  server.handleClient();

  delay(dht.getMinimumSamplingPeriod());

  humedad =  dht.getHumidity();
  temperatura = dht.getTemperature();

  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("No se pudo leer sensor DHT!");
    return;
  }
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humedad, 1);
  Serial.print("\t\t");
  Serial.print(temperatura, 1);
  Serial.print("\t\t");
  Serial.print(dht.toFahrenheit(temperatura), 1);
  Serial.print("\t\t");
  Serial.print(dht.computeHeatIndex(temperatura, humedad, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperatura), humedad, true), 1);
  delay(2000);
}

void controlarIndex() {
  server.send(200, "text/html", escribirHTML(humedad, temperatura)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Error! Not found");
}

String escribirHTML(float humedad, float temperatura){
  String ptr = "<!DOCTYPE html>";
  ptr += "<html>";
  ptr += "<body>";
  ptr += "<h2>ESP32 Wi-Fi + Temperatura</h2>";
  ptr += "<form action\"/\">";
  ptr += "<label for=\"hum\">Humedad:</label>";
  ptr += "<input type=\"text\" id=\"humedity\" value=\"";
  ptr += humedad;
  ptr += "\">\t";
  ptr += "<label for=\"temp\">Temperatura:</label>";
  ptr += "<input type=\"text\" id=\"temperature\" value=\"";
  ptr += temperatura;
  ptr += "\"><br><br>";
  ptr += "<input type=\"submit\" value=\"Recargar\">";
  ptr += "</form>";
  ptr += "</body>";
  ptr += "</html>";
  return ptr;
}
