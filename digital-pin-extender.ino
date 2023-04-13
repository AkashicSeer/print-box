#include <light_CD74HC4067.h>
//list of mux input pins
#define S0_PIN D0
#define S1_PIN D8
#define S2_PIN D3
#define S3_PIN D4
#define SIG_PIN D7
CD74HC4067 mux(S0_PIN, S1_PIN, S2_PIN, S3_PIN);

//pins are from 0 to 15, highLow is whether to set the pin to either HIGH or LOW
void setMuxOutputPin(int pinNumber, int highLow) {
  pinMode(SIG_PIN, OUTPUT);
  Serial.println("Setting pin extender pin " + String(pinNumber) + " to " + String(highLow));
  mux.channel(pinNumber);
  digitalWrite(pinNumber, highLow);
}