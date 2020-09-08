//
// Created by Juscelino Tanaka on 06/09/20.
//

#include "ConnectionCallbacks.h"

ConnectionCallbacks::ConnectionCallbacks(bool * refConnected) {
    connectedReference = refConnected;
}

void ConnectionCallbacks::onConnect(BLEServer* pServer) {
    *connectedReference = true;

    if (callback != nullptr) {
        callback(true);
    }
}

void ConnectionCallbacks::onDisconnect(BLEServer* pServer) {
    *connectedReference = false;

    if (callback != nullptr) {
        callback(false);
    }
}

void ConnectionCallbacks::registerCallback(void (*f)(bool)) {
    callback = f;
}
