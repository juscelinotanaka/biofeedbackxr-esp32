#include <Arduino.h>
#include "DisplayManager.h"
#include "BluetoothService.h"

int dly = 10;

DisplayManager display;
BluetoothService bleService;

void setup(void) {
    randomSeed(analogRead(0)*analogRead(1));
    display.init();
    display.initialMessage();
    bleService.setup();
}

void loop() {
    display.setTime(millis());
    display.printPage();
    // BLE service needs to be latest because it'll delay to prevent flooding BLE service
    // TODO: make it not lock main thread
    bleService.update();
}