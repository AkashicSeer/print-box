#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;

void setupBME280() {
   bme.begin(0x76);
}

float getBME280TempC() {
  return bme.readTemperature();
}

float getBME280Humidity() {
  return bme.readHumidity();
}

float getBME280Barometric() {
  return (bme.readPressure() / 100.0F);
}
/*
Tries to guess the Altitude, not very accurate, based on Barometric pressure
*/
float getAltitudeGuess(){
 return bme.readAltitude(SEALEVELPRESSURE_HPA);
}