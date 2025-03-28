#pragma once
#include "serial.h"
#include "screen.h"

#ifdef SERIAL_INFO
#   if SERIAL_MAX_LINES > OLED_MAX_LINES
#       define INFO_MAX_LINES SERIAL_MAX_LINES
#   else
#       define INFO_MAX_LINES OLED_MAX_LINES
#   endif
#else
#   define INFO_MAX_LINES OLED_MAX_LINES
#endif


namespace info {

void setup() {
    serial::setup();
    screen::setup();
}

template<typename T> void line(T text, uint8_t lineno = 0) {
    screen::set_line(text, lineno);
    serial::set_line(text, lineno);
}

template<typename T> void lines(T lines[], int n) {
    screen::set_lines(lines, n);
    serial::set_lines(lines, n);
}

template<typename T> void status(T text) {
    line(text, 5);
}

template<typename T> void status2(T text) {
    line(text, 6);
}

void loop() {
    screen::loop();
    serial::loop();
}

}
