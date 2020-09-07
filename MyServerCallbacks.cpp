//
// Created by Juscelino Tanaka on 06/09/20.
//

#include "MyServerCallbacks.h"

MyServerCallbacks::MyServerCallbacks(bool *variable) {
    deviceConnected = variable;
}

void MyServerCallbacks::onConnect(BLEServer* pServer) {
    *deviceConnected = true;
}

void MyServerCallbacks::onDisconnect(BLEServer* pServer) {
    *deviceConnected = false;
}