#include "Adafruit_HTU21DF.h"
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

void htu21dSetup() {
  htu.begin();
}

float getHTU21DTempInC() {
  return htu.readTemperature();
}

float getHTU21DHumidity() {
  return htu.readHumidity();
}