*
    Fuente: https://circuits4you.com/2019/01/25/esp32-dht11-22-humedad-temperatura-sensor-interfacing-example/

   ESP32 NodeMCU DHT11 - humedad temperatura Sensor Example
   https://circuits4you.com

   References
   https://circuits4you.com/2017/12/31/nodemcu-pinout/

*/

#include "DHTesp.h"

#define DHTpin 15    //D15 del ESP32 DevKit

DHTesp dht;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Estado\tHumedad (%)\tTemperatura (C)\t(F)\tIndiceCalor (C)\t(F)");

  // Autodetect is not working reliable, don't use the following line
  // dht.setup(17);

  // use this instead:
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
  //dht.setup(DHTpin, DHTesp::DHT22); //for DHT22 Connect DHT sensor to GPIO 17
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humedad =  dht.getHumidity();
  float temperatura = dht.getTemperature();

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
