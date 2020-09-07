//
// Created by Juscelino Tanaka on 06/09/20.
//

#ifndef BIO_FEEDBACK_XR_BLUETOOTHSERVICE_H
#define BIO_FEEDBACK_XR_BLUETOOTHSERVICE_H

#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <TFT_eSPI.h>

#include "ConnectionCallbacks.h"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class BluetoothService {
public:
    void setup();
    BLEServer *pServer = NULL;
    BLECharacteristic * pTxCharacteristic;
    bool deviceConnected = false;
    bool oldDeviceConnected = false;
    uint8_t txValue = 41;

    void update();
    ConnectionCallbacks serverCallbacks = ConnectionCallbacks(&deviceConnected);

private:
    class CharacteristicCallback: public BLECharacteristicCallbacks {
        void onWrite(BLECharacteristic *pCharacteristic) {
            std::string rxValue = pCharacteristic->getValue();

            if (rxValue.length() > 0) {
                Serial.println("*********");
                Serial.print("Received Value: ");
                for (int i = 0; i < rxValue.length(); i++)
                    Serial.print(rxValue[i]);

                Serial.println();
                Serial.println("*********");
            }
        }
    };
};

#endif //BIO_FEEDBACK_XR_BLUETOOTHSERVICE_H
