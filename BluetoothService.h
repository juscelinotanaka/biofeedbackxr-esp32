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
    void update(unsigned long time);
    void setData(uint16_t ecg, uint16_t emg);
    void registerDeviceConnected(void (*f)(bool));

private:
    const unsigned long delayTime = 10;

    ConnectionCallbacks serverCallbacks = ConnectionCallbacks(&deviceConnected);

    BLEServer *pServer = NULL;
    BLECharacteristic * pTxCharacteristic;
    bool deviceConnected = false;
    bool oldDeviceConnected = false;

    static const size_t dataSize = 8;
    uint8_t data[dataSize];
    uint8_t * ptrData = data;

    unsigned long lastUpdate = 0;

    //TODO: move this to an independent file
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
