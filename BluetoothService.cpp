//
// Created by Juscelino Tanaka on 06/09/20.
//

#include "BluetoothService.h"

void BluetoothService::setup() {
    Serial.begin(115200);

    // Create the BLE Device
    BLEDevice::init("UARTService");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(&serverCallbacks);

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pTxCharacteristic = pService->createCharacteristic(
            CHARACTERISTIC_UUID_TX,
            BLECharacteristic::PROPERTY_NOTIFY
    );

    pTxCharacteristic->addDescriptor(new BLE2902());

    BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
            CHARACTERISTIC_UUID_RX,
            BLECharacteristic::PROPERTY_WRITE
    );

    pRxCharacteristic->setCallbacks(new CharacteristicCallback());

    // Start the service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();
    Serial.println("Waiting a client connection to notify...");
}

void BluetoothService::update(unsigned long time) {
    if (time >= lastUpdate + delayTime && deviceConnected) {
        data[0] = (time >> 24) & 0xFF;
        data[1] = (time >> 16) & 0xFF;
        data[2] = (time >> 8) & 0xFF;
        data[3] = time & 0xFF;

        pTxCharacteristic->setValue(ptrData, dataSize);
        pTxCharacteristic->notify();

        lastUpdate = time;
    }

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }

    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}

void BluetoothService::registerDeviceConnected(void (*f)(bool)) {
    serverCallbacks.registerCallback(f);
}

void BluetoothService::setData(uint16_t ecg, uint16_t emg) {
    data[4] = (ecg >> 8) & 0xFF;
    data[5] = ecg & 0xFF;

    data[6] = (emg >> 8) & 0xFF;
    data[7] = emg & 0xFF;
}