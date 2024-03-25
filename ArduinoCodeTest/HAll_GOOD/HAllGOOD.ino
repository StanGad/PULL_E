#include <Wire.h>
#include <AS5600.h>

#define SERIAL Serial
#define SYS_VOL   5

AS5600 ams5600; // Change AMS_5600 to AS5600
int ang, lang = 0;
int multiplexer_address = 0x70; // Address of your PCA9548A multiplexer

void setup()
{
  SERIAL.begin(9600);
  Wire.begin();
  SERIAL.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> ");
  
  // Select the appropriate channel on the multiplexer
  Wire.beginTransmission(multiplexer_address);
  Wire.write(1 << 2); // Select channel 2 (bit 2)
  Wire.endTransmission();

  // Check if magnet is detected
  if (ams5600.detectMagnet() == 0) {
    while (1) {
      if (ams5600.detectMagnet() == 1) {
        SERIAL.print("Current Magnitude: ");
        SERIAL.println(ams5600.readMagnitude());
        break;
      } else {
        SERIAL.println("Can not detect magnet");
      }
      delay(1000);
    }
  }
}

float convertRawAngleToDegrees(word newAngle)
{
  /* Raw data reports 0 - 4095 segments, which is 0.087890625 of a degree */
  float retVal = newAngle * 0.087890625;
  return retVal;
}

void loop()
{
  // Read angle from AS5600 sensor
  SERIAL.println(String(convertRawAngleToDegrees(ams5600.readAngle()), DEC));
}
