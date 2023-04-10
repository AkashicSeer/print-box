#define PIN_NUM D1
void initializeRelayPins() {
  pinMode(PIN_NUM, OUTPUT);
}
/*
highLow : 1 for high 0 for low High turns the relay on, low turns it off
*/
void toggleRelayPin(int pinNumber, int highLow) {
  if (highLow > 0) {
    digitalWrite(pinNumber, HIGH);
  } else {
    digitalWrite(pinNumber, LOW);
  }
}

