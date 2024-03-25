#include <Wire.h>
#include <AS5600.h>

#define SERIAL Serial

AS5600 ams5600; // AS5600 object

void setup() {
  SERIAL.begin(9600);
  Wire.begin();

  SERIAL.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> ");
  
  // Initialize AS5600 with the default address
  ams5600.begin();

  // Check if magnet is detected
  if(!ams5600.detectMagnet()) {
    SERIAL.println("Can not detect magnet");
  } else {
    SERIAL.print("Current Magnitude: ");
    SERIAL.println(ams5600.readMagnitude());
  }
}

// Function to convert raw angle to degrees
float convertRawAngleToDegrees(word newAngle) {
  // Raw data reports 0 - 4095 segments, which is 0.087890625 of a degree
  float retVal = newAngle * 0.087890625;
  return retVal;
}

void loop() {
  // Read and print the angle in degrees
  delay(200);
  SERIAL.println(String(convertRawAngleToDegrees(ams5600.readAngle()), DEC));
}
