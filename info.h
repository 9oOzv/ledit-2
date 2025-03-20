#pragma once
#include <Arduino.h>
#include "screen.h"
#include "serial.h"

#define INFO_NUM_LINES 7
#define INFO_LINE_HEIGHT 9

namespace info {

using screen::Screen;


class Info : public Screen {
public:

    void setup() {
        if(_setup) return;
        serial::setup();
        Screen::setup();
        info("Ready");
        _setup = true;
    }

    void loop() {
        loop_serial();
        loop_oled();
    }

    void loop_serial() {
        unsigned long t = millis();
        if(t - t_serial < 2000) return;
        for(uint8_t i = 0; i < INFO_NUM_LINES; i++) {
            serial::line(lines[i]);
        }
        t_serial = t;
    }

    void loop_oled() {
        display.clearDisplay();
        for(uint8_t i = 0; i < INFO_NUM_LINES; i++) {
            display.setCursor(0, i * INFO_LINE_HEIGHT);
            display.print(lines[i]);
        }
        display.display();
    }
    
    template <typename T> void info(T text) { lines[INFO_NUM_LINES-1] = text; }
    template <typename T> void line(T text, uint8_t lineno = 0) { lines[lineno] = text; }

private:
    Screen screen;
    String lines[INFO_NUM_LINES];
    unsigned long t_serial = 0;
};


Info info;


void line(String text, uint8_t lineno = 0) { info.line(text, lineno); }
void setup() { info.setup(); }
void loop() { info.loop(); }


}  // namespace info
