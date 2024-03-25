#include "Wire.h"
#include "Adafruit_TCS34725.h"

// Définissez l'adresse I2C du capteur
#define TCS34725_ADDRESS 0x29

// Définissez les broches pour les LED
#define redpin 3
#define greenpin 5
#define bluepin 6

// Définissez si vous utilisez une LED à cathode commune
#define commonAnode true

// Table de correction gamma
byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725();

void setup() {
  Serial.begin(9600);
  Serial.println("Test de vision des couleurs !");

  // Configuration des broches pour les LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // Initialisation du capteur avec les paramètres par défaut
  if (!tcs.begin()) {
    Serial.println("Error initializing TCS34725 sensor!");
    while (1);
  }

  // Création de la table de correction gamma
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
 
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }
}

void loop() {
  float red, green, blue;
  
  // Lecture des valeurs RGB du capteur
  delay(200);  // Attendre 200 ms pour lire
  tcs.getRGB(&red, &green, &blue);

  // Affichage des valeurs RGB
  Serial.print("R:\t"); Serial.print(int(red));
  Serial.print("\tG:\t"); Serial.print(int(green));
  Serial.print("\tB:\t"); Serial.print(int(blue));
  Serial.print("\n");
 
  // Réglage des broches PWM pour les LED avec la table de correction gamma
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);
}
