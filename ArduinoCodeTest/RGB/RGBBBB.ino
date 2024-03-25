#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

uint16_t prevR, prevG, prevB, prevC;
const int colorThreshold = 200; // Adjust this threshold as needed

void setup(void) {
  Serial.begin(9600);

  if (!tcs.begin()) {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Now we're ready to get readings!

  // Change the I2C address to 0x77
 // tcs.setAddress(0x77);

  // Verify if the address change was successful
  if (!tcs.begin()) {
    Serial.println("No TCS34725 found at new address ... check your connections");
    while (1);
  }

  Serial.println("Found sensor at new address");

  // Initialize previous color readings
  tcs.getRawData(&prevR, &prevG, &prevB, &prevC);
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  // Check for a change in color
  if (abs(r - prevR) > colorThreshold || abs(g - prevG) > colorThreshold || abs(b - prevB) > colorThreshold || abs(c - prevC) > colorThreshold) {
    Serial.println("Change in color detected!");
  }

  // Update previous color readings
  prevR = r;
  prevG = g;
  prevB = b;
  prevC = c;

  delay(100); // Wait for 1 second before taking the next reading
}
