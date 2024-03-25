#include <Wire.h>
#include <Adafruit_TCS34725.h>

#define PCA9548A_ADDRESS 0x70
#define TCS34725_ADDRESS 0x29

#define CHANNEL_7_BIT (1 << 7)

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Select channel 7 of the PCA9548A multiplexer
  Wire.beginTransmission(PCA9548A_ADDRESS);
  Wire.write(CHANNEL_7_BIT);
  Wire.endTransmission();

  Serial.println("Selected channel 7 of the PCA9548A multiplexer");
}


void loop() {
  // Read color data from TCS34725 sensor
  uint16_t clear, red, green, blue;
  
  Wire.beginTransmission(TCS34725_ADDRESS); // TCS34725's address
  Wire.write(0x80 | 0x12); // Command register AND multi-byte flag
  Wire.endTransmission(false);
  Wire.requestFrom(TCS34725_ADDRESS, 2); // Request 2 bytes from TCS34725
  red = Wire.read(); // Read red value
  red |= Wire.read() << 8;
  Wire.requestFrom(TCS34725_ADDRESS, 2); // Request 2 bytes from TCS34725
  green = Wire.read(); // Read green value
  green |= Wire.read() << 8;
  Wire.requestFrom(TCS34725_ADDRESS, 2); // Request 2 bytes from TCS34725
  blue = Wire.read(); // Read blue value
  blue |= Wire.read() << 8;
  Wire.requestFrom(TCS34725_ADDRESS, 2); // Request 2 bytes from TCS34725
  clear = Wire.read(); // Read clear value
  clear |= Wire.read() << 8;

  Serial.print("Clear: "); Serial.print(clear);
  Serial.print(" Red: "); Serial.print(red);
  Serial.print(" Green: "); Serial.print(green);
  Serial.print(" Blue: "); Serial.print(blue);

  // Calculate color temperature
  float temp = tcs.calculateColorTemperature(red, green, blue);
  Serial.print(" Color Temp: "); Serial.print(temp); Serial.println(" K");

  // Calculate lux
  float lux = tcs.calculateLux(red, green, blue);
  Serial.print(" Lux: "); Serial.println(lux);

  delay(1000); // Adjust as needed for your application
}
