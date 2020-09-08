#include <Arduino.h>
#include "DisplayManager.h"
#include "BluetoothService.h"

unsigned long now;

DisplayManager display;
BluetoothService bleService;

void onDeviceConnected(bool);

void setup(void) {
    randomSeed(analogRead(0)*analogRead(1));
    display.init();
    display.initialMessage();
    bleService.registerDeviceConnected(&onDeviceConnected);
    bleService.setup();
}

void onDeviceConnected(bool connected) {
    display.setClientConnected(connected);
}

void loop() {
    now = millis();
    display.printPage();

    // BLE service needs to be latest because it'll delay to prevent flooding BLE service
    // TODO: make it not lock main thread
    bleService.update(now);
}