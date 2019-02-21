#include <RX2.h>

#define ANTENNA 1
#define BUTTON_SW 0

RX2 car(ANTENNA);

volatile bool buttonPressed = false;
void buttonAsyncFunc() {
  buttonPressed = digitalRead(BUTTON_SW) == HIGH;
  digitalWrite(LED_BUILTIN, LOW);
  car.next(RX2_ENDCODE);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_SW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_SW), buttonAsyncFunc, CHANGE);
}

void loop() {
  if (buttonPressed) {
    digitalWrite(LED_BUILTIN, HIGH);
    car.write(RX2_BACKWARD);
  }
  car.update();
}