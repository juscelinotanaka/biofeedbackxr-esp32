//
// Created by Juscelino Tanaka on 06/09/20.
//

#ifndef BIO_FEEDBACK_XR_MYSERVERCALLBACKS_H
#define BIO_FEEDBACK_XR_MYSERVERCALLBACKS_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <TFT_eSPI.h>

class MyServerCallbacks: public BLEServerCallbacks {
public:
    MyServerCallbacks(bool * variable);

private:
    bool * deviceConnected;
    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);
};


#endif //BIO_FEEDBACK_XR_MYSERVERCALLBACKS_H
