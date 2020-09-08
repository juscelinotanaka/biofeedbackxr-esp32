//
// Created by Juscelino Tanaka on 09/09/20.
//

#include "ECGReader.h"

ECGReader::ECGReader(uint8_t plusPin, uint8_t minusPin, uint8_t analogPin) {
    this->plusPin = plusPin;
    this->minusPin = minusPin;
    this->analogPin = analogPin;
}

void ECGReader::setup() {
    pinMode(plusPin, INPUT);
    pinMode(minusPin, INPUT);
}

uint16_t ECGReader::getValue() {
    return value;
}

void ECGReader::update(unsigned long time) {
    if (time > lastUpdateTime + 10) {
        lastUpdateTime = time;

        if ((digitalRead(plusPin) == 1) || (digitalRead(minusPin) == 1)) {
            Serial.println('!');
        } else {
            value = analogRead(analogPin);
            Serial.println(value);
        }
    }
}
