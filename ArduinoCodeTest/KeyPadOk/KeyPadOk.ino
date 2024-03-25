#include "U8glib.h"
#include <Keypad.h>
#include <AccelStepper.h>

#define STEP_PIN 4
#define DIR_PIN 5

// Initialize the OLED display object
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

// Define the keypad pins and create the Keypad object
const byte ROWS = 4; /*Define Keypad Rows*/
const byte COLS = 4; /*Define Keypad Columns*/
char Keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte rowPins[ROWS] = {7};  /*Initialized Arduino Pins for Rows*/
byte colPins[COLS] = {8,9,10};     /*Initialized Arduino Pins for Columns*/
Keypad myKeypad = Keypad(makeKeymap(Keys), rowPins, colPins, ROWS, COLS); /*Function for Keypad*/

int currentCase = 0;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  Serial.begin(9600);
  u8g.begin();
  stepper.setMaxSpeed(500); 
  stepper.setAcceleration(500);
}

bool stopMotor = false; // Variable pour arrêter le moteur

void loop() {
  char key = myKeypad.getKey();
  if (key == '1') {
    currentCase = (currentCase + 1) % 5;
    stopMotor = true; // Définir la variable d'arrêt à true lorsque vous changez de cas
    displayCurrentCase();
    stopMotor = false; // Réinitialiser la variable d'arrêt lorsque vous sortez de la fonction displayCurrentCase()
  }
}

void displayCurrentCase() {
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.setPrintPos(0, 20);
    switch (currentCase) {
      case 0:
        u8g.print("LiftUp and Down");
        handleMotorControl();
        break;
      case 1:
        u8g.print("Calibration");
        break;
      case 2:
        u8g.print("Up & Down Auto");
        upAndDownAuto();
        break;
      case 3:
        u8g.print("Display Values");
        break;
      case 4:
        u8g.print("Nothing");
        break;
    }
  } while( u8g.nextPage() );
}

void handleMotorControl() {
  char key = myKeypad.getKey();
  if ((key == '2' || key == '3') && !stopMotor) {
    int direction = (key == '2') ? 1 : -1; // 1 pour dans le sens horaire, -1 pour dans le sens antihoraire
    stepper.setSpeed(100 * direction); // Définir la vitesse avec la direction
    stepper.setAcceleration(500); // Définir l'accélération
    stepper.move(1000 * direction); // Déplacer le moteur dans la direction spécifiée
    while (myKeypad.getKey() == key && !stopMotor) {
      if (stepper.distanceToGo() == 0) // Vérifier si le moteur a atteint sa position cible
        break;
      stepper.run();
    }
    stepper.stop(); // Arrêter le moteur lorsque le bouton est relâché ou que la position cible est atteinte
  }
}


void upAndDownAuto() {
  stepper.moveTo(1000); // Move 1000 steps forward
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  delay(1000); // Pause for a moment

  stepper.moveTo(0); // Move back to the initial position
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  delay(1000); // Pause for a moment
}
