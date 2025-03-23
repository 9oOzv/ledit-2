#pragma once
#include <Arduino.h>

#define SERIAL_MAX_LINES 7
#define SERIAL_INTERVAL 2000




#ifdef SERIAL_INFO

namespace serial {

String lines[SERIAL_MAX_LINES];
unsigned long last = 0;

void setup() {
    if (SERIAL_INFO && !Serial) {
        Serial.begin(115200);
        delay(6000);
        Serial.println();
    }
}

template <typename T> void set_line(T text, uint8_t lineno) {
    if(lineno >= SERIAL_MAX_LINES) return;
    lines[lineno] = String(text);
}

template <typename T> void set_lines(T lines[], int n) {
    for (int i = 0; i < n; i++) set_line(lines[i], i);
}

template <typename T> void println(T text) {
    if (!SERIAL_INFO || !Serial) return;
    String s(text);
    if (s.length() + 2 > Serial.availableForWrite()) return;
    Serial.println(s);
}

void loop() {
    if (!SERIAL_INFO || !Serial) return;
    if (millis() - last < SERIAL_INTERVAL) return;
    last = millis();
    for (int i = 0; i < SERIAL_MAX_LINES; i++) Serial.println(lines[i]);
}

}  // namespace serial




#else // SERIAL_INFO

namespace serial {

void setup() {}
template <typename T> void set_line(T text, uint8_t lineno) {}
template <typename T> void set_lines(T lines[], int n) { }
template <typename T> void println(T text) {}
void loop() {}

}  // namespace serial

#endif // ! SERIAL_INFO
