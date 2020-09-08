#include <Arduino.h>
#include "DisplayManager.h"
#include "BluetoothService.h"
#include "ECGReader.h"

unsigned long now;

DisplayManager display;
BluetoothService bleService;
int8_t ecgPlusPin = 32;
int8_t ecgMinusPin = 39;
int8_t ecgAnalogPin = A0;
ECGReader ecgReader = ECGReader(ecgPlusPin, ecgMinusPin, ecgAnalogPin);

void onDeviceConnected(bool);

void setup(void) {
    display.init();
    display.initialMessage();

    ecgReader.setup();

    bleService.setup();
    bleService.registerDeviceConnected(&onDeviceConnected);
}

void onDeviceConnected(bool connected) {
    display.setClientConnected(connected);
}

void loop() {
    now = millis();
    display.printPage();

    // ECG
    ecgReader.update(now);

    //TODO: make a condition to know when BLE Service is about to dispatch, then read data only when it will send
    // and update display by there as well
    bleService.setData(ecgReader.getValue(), 0xEE);
    bleService.update(now);
}