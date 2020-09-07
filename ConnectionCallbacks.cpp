//
// Created by Juscelino Tanaka on 06/09/20.
//

#include "ConnectionCallbacks.h"

ConnectionCallbacks::ConnectionCallbacks(bool *variable) {
    deviceConnected = variable;
}

void ConnectionCallbacks::onConnect(BLEServer* pServer) {
    *deviceConnected = true;
}

void ConnectionCallbacks::onDisconnect(BLEServer* pServer) {
    *deviceConnected = false;
}