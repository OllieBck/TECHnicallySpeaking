#include <Stepper.h>

const int ledPin = 13;
const int stepsPer = 200;
int incomingByte;

Stepper lightStepper(stepsPer, 8, 6, 5, 4);

void setup() {
  Serial.begin(115200);
  lightStepper.setSpeed(60);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'U') {
      digitalWrite(ledPin, HIGH);
      lightStepper.step(stepsPer);
      delay(500);
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'D') {
      digitalWrite(ledPin, LOW);
      lightStepper.step(-stepsPer);
      delay(500);
    }
  }
}
