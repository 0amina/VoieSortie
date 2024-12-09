#include <Arduino.h>
#include "lights.h"
#include "barrier.h"
#include "sensors.h"

#define DE_PIN 32 // DE
#define BO_PIN 33 // BO
#define DS_PIN 25 // DS

#define RED_LIGHT_PIN 23
#define ORANGE_LIGHT_PIN 22
#define GREEN_LIGHT_PIN 21
#define BARRIER_LIGHT_PIN 19

unsigned long orangeBlinkStart = 0;
const unsigned long orangeBlinkInterval = 100; // 10 Hz
bool orangeBlinkState = false;

void setup() {
  pinMode(DE_PIN, INPUT);
  pinMode(BO_PIN, INPUT);
  pinMode(DS_PIN, INPUT);

  setupLights(RED_LIGHT_PIN, ORANGE_LIGHT_PIN, GREEN_LIGHT_PIN);
  setupBarrier(BARRIER_LIGHT_PIN);

  turnOnRedLight();
  closeBarrier();
}

void loop() {
  bool deState = digitalRead(DE_PIN);
  bool boState = digitalRead(BO_PIN);
  bool dsState = digitalRead(DS_PIN);

  if (!deState) { // No vehicle detected
    turnOnRedLight();
    closeBarrier();
    return;
  }

  if (boState) { // Button pressed
    openBarrier();
    turnOnGreenLight();

    if (dsState) { // Vehicle passed the barrier
      delay(1000); // Wait 1 second
      turnOnRedLight();
      closeBarrier();
    }
    return;
  }

  // Vehicle detected but no button pressed
  if (!dsState) {
    if (millis() - orangeBlinkStart >= 20000) {
      if (millis() - orangeBlinkStart >= orangeBlinkInterval) {
        orangeBlinkStart = millis();
        orangeBlinkState = !orangeBlinkState;
        setOrangeLight(orangeBlinkState);
      }
    }
  }
}
