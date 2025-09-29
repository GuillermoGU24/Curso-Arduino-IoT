#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHTll

DHT dht (DHTPIN, DHTTYPE);

void setup() {

Serial.begin(9600);
dht.begin();

}


void loop() {

delay(2000);
float humedad = dht.readHumidity();
float temperatura = dht.readTemperature();
  if (isnan(humedad) || isnan(temperatura)){
   Serial.println("Error al leer del sensor DHT11");
  return;
   }
Serial.print("Humedad: ");
Serial.print(humedad);
Serial.print("% ");
Serial.print("Temperatura");
Serial.print(temperatura);
Serial.println("°C");
}