#include <Wire.h>
#include <ESP8266WiFi.h>

void setup(void) {
  // start serial port
  Serial.begin(115200);
  delay(100);
  while (!Serial) {
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens
  }

  delay(5000);
  screenSetup();
  // Start I2C communication with the Multiplexer
  Wire.begin();

  switchI2cMuxPin(7);

  String serverAddress = setupServer();
  sendToScreen(serverAddress);
}

void loop(void) {
  handleRequest();
}
