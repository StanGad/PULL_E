#include <AccelStepper.h>

// Define the pins connected to the motor
#define STEP_PIN 4
#define DIR_PIN 5

// Create a new instance of the AccelStepper class
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(500); // Adjust the speed as needed
  stepper.setAcceleration(500); // Adjust the acceleration as needed
  
  // Set the initial direction
  stepper.setSpeed(100); // Set the speed and direction (positive for forward, negative for reverse)
}

void loop() {
  // Move the motor forward
  stepper.moveTo(1000); // Move 1000 steps forward
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  // Pause for a moment


  // Move the motor backward
  stepper.moveTo(0); // Move back to the initial position
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  // Pause for a moment
 
}
