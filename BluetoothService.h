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

    /**
     * Pack the data (time + ECG data + EMG data) and notify it if enough time has passed after the previous
     * dispatch. Ypi cam ise willDispatch to check if a dispatch will happen or not by a specific time (preferably now)
     * @param time in millis
     */
    void dispatch(unsigned long time);

    /**
     * Check whether a device disconnected or connected
     * @param time in millis
     */
    void update(unsigned long time);

    /**
     * Sets the data for ECG and EMG devices which will be sent during update
     */
    void setData(uint16_t, uint16_t);

    /**
     * Register a callback to know when a device was connected or not
     * @param f A void function(bool) delegate
     */
    void registerDeviceConnected(void (*f)(bool));

    /**
     * Check whether the bluetooth service will dispatch/sync data at the given time or not. E.g. it can be used
     * to check if it will dispatch events now or in a future time.
     * @return true if time >= lastUpdate + delayTime
     */
    bool willDispatch(unsigned long);

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
