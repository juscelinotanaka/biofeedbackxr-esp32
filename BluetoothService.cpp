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
    Serial.print("T: ");
    Serial.println(time);
    Serial.println(lastUpdate);
    Serial.println(deviceConnected);

    if (time >= lastUpdate + delayTime && deviceConnected) {
        pTxCharacteristic->setValue(&txValue, 1);
        pTxCharacteristic->notify();
        txValue++;
        if (txValue > 126)
            txValue = 41;

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