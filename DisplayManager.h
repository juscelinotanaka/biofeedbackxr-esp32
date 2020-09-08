//
// Created by Juscelino Tanaka on 06/09/20.
//
#include <Arduino.h>
#ifndef BIO_FEEDBACK_XR_DISPLAYMANAGER_H
#define BIO_FEEDBACK_XR_DISPLAYMANAGER_H

#include <SPI.h>
#include <TFT_eSPI.h>

static uint8_t conv2d(const char* p) {
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}

class DisplayManager {
public:
    void init();
    void initialMessage();
    void setClientConnected(bool connected);
    void printPage();
    void fillScreen();

private:
    int16_t h = 135;
    int16_t w = 240;
    unsigned long messageDelay = 500;
    unsigned long currentTime;
    String hh = String(conv2d(__TIME__));
    String mm = String(conv2d(__TIME__+3));
    String buildString = String("Build: 0." + hh + "." + mm);
    TFT_eSPI tft = TFT_eSPI(h, w);
};


#endif //BIO_FEEDBACK_XR_DISPLAYMANAGER_H
