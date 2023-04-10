#include "ClosedCube_HDC1080.h"

ClosedCube_HDC1080 hdc1080;

void setupHDC1080() {
  hdc1080.begin(0x40);
  printSerialNumber();
}

float getHdc1080Humidity() {
  return hdc1080.readHumidity();
}
float getHdc1080TemperatureInC() {
  return hdc1080.readTemperature();
}
void printSerialNumber() {
  Serial.print("Device Serial Number=");
  HDC1080_SerialNumber sernum = hdc1080.readSerialNumber();
  char format[12];
  sprintf(format, "%02X-%04X-%04X", sernum.serialFirst, sernum.serialMid, sernum.serialLast);
  Serial.println(format);
}