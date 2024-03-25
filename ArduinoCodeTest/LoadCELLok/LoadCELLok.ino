#include "HX711.h"

#define DOUT 3
#define CLK 2

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT, CLK);
}

void loop() {
  Serial.print("Reading: ");
  Serial.println(scale.read());
  delay(1000);
}
