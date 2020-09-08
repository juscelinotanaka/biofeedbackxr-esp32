//
// Created by Juscelino Tanaka on 09/09/20.
//

#ifndef BIO_FEEDBACK_XR_ECGREADER_H
#define BIO_FEEDBACK_XR_ECGREADER_H

#include <Arduino.h>

class ECGReader {
public:
    ECGReader(uint8_t plusPin, uint8_t minusPin, uint8_t analogPin);
    void setup();
    void update(unsigned long);
    uint16_t getValue();

private:
    uint8_t plusPin;
    uint8_t minusPin;
    uint8_t analogPin;

    uint16_t value;
    int lastUpdateTime = 0;
};


#endif //BIO_FEEDBACK_XR_ECGREADER_H
