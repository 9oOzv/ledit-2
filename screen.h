#pragma once
#include <Arduino.h>
#include "error.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C
#define OLED_CLK 800000UL

namespace screen {


class Screen {
public:

    void setup() {
        if(_setup) return;
        Wire.begin(14, 12);
        display = Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET, OLED_CLK);
        if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) fatal(F("SSD1306 allocation failed"));
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.cp437(true);
        display.setTextWrap(false);
        display.clearDisplay();
        display.display();
        _setup = true;
    }

    void loop();

protected:
    Adafruit_SSD1306 display;
    bool _setup = false;
};


}  // namespace screen
