#include "U8glib.h"
#include "HX711.h"

// Define pin constants for the HX711
#define DOUT 3
#define CLK 2

// Initialize the HX711 object
HX711 scale;

// Initialize the OLED display object
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup(void) {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Start the communication with the OLED display
  u8g.begin();
  
  // Initialize the HX711 load cell sensor
  scale.begin(DOUT, CLK);
}

void loop(void) {
  // Read the value from the load cell
  long reading = scale.read();

  // Clear the display
  u8g.firstPage();  
  do {
    // Print "hello" at position (0, 20)
    u8g.setFont(u8g_font_unifont);
    u8g.setPrintPos(0, 20);
    u8g.print("Load Cell Value:");
    u8g.setPrintPos(0, 40);
    u8g.print(reading); // Print the reading from the load cell
  } while( u8g.nextPage() );

  // Print the value to Serial monitor
  Serial.print("Load Cell Reading: ");
  Serial.println(reading);

  // Add some delay before updating again
  delay(200);
}
