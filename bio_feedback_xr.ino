#include <Arduino.h>
#include "DisplayManager.h"

int dly = 10;

DisplayManager display;

void setup(void) {
    randomSeed(analogRead(0)*analogRead(1));
    display.init();
    display.initialMessage();
}

void loop() {
    display.setTime(millis());
    display.printPage();
    delay(dly);
}
