#pragma once
#include <Arduino.h>

namespace serial {


void setup() {
    if (DEBUG && !Serial) {
        Serial.begin(115200);
        delay(6000);
    }
}


template <typename T> void line(T text) {
    if (DEBUG && Serial) Serial.println(text);
}


}
