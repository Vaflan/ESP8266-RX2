#include <RX2.h>

#define ANTENNA 1

RX2 car(ANTENNA);

void setup() {
}

void loop() {
  car.update();
  car.write(RX2_FORWARD);
}