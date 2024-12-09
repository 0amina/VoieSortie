#include <Arduino.h>
#include "lights.h"

int redLightPin, orangeLightPin, greenLightPin;

void setupLights(int redPin, int orangePin, int greenPin) {
  redLightPin = redPin;
  orangeLightPin = orangePin;
  greenLightPin = greenPin;

  pinMode(redLightPin, OUTPUT);
  pinMode(orangeLightPin, OUTPUT);
  pinMode(greenLightPin, OUTPUT);
}

void turnOnRedLight() {
  digitalWrite(redLightPin, HIGH);
  digitalWrite(orangeLightPin, LOW);
  digitalWrite(greenLightPin, LOW);
}

void turnOnGreenLight() {
  digitalWrite(redLightPin, LOW);
  digitalWrite(orangeLightPin, LOW);
  digitalWrite(greenLightPin, HIGH);
}

void setOrangeLight(bool state) {
  digitalWrite(orangeLightPin, state ? HIGH : LOW);
}
