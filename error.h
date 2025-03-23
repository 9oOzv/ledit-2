#pragma once
#include <Arduino.h>
#include "serial.h"

template<typename T> void fatal(T text) {
    serial::setup();
    for(;;) {
        serial::println(text);
        delay(1000);
    }
}
