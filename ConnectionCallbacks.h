//
// Created by Juscelino Tanaka on 06/09/20.
//

#ifndef BIO_FEEDBACK_XR_CONNECTIONCALLBACKS_H
#define BIO_FEEDBACK_XR_CONNECTIONCALLBACKS_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <TFT_eSPI.h>

class ConnectionCallbacks: public BLEServerCallbacks {
public:
    ConnectionCallbacks(bool * variable);

private:
    bool * deviceConnected;
    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);
};


#endif //BIO_FEEDBACK_XR_CONNECTIONCALLBACKS_H
