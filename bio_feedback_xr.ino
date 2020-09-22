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
    bleService.update(now);

    if (bleService.willDispatch(now)) {
        // ECG
        ecgReader.update(now);
        uint16_t ecgValue = ecgReader.getValue();

        bleService.setData(ecgValue, 0xEE);
        bleService.dispatch(now);

        display.printPage();
    }
}