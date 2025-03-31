#pragma once
#include <Arduino.h>
#include "error.h"
#include "common.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C
#define OLED_CLK 800000UL
#define OLED_MAX_LINES 8
#define OLED_LINE_HEIGHT OLED_HEIGHT / OLED_MAX_LINES
#define OLED_LINE_SCROLL_SPEED 100
#define OLED_ROTATION 2


#ifdef OLED_INFO

namespace screen {

Adafruit_SSD1306 display;
String lines[OLED_MAX_LINES];
uint16_t scroll = 0;
unsigned long last_scroll_update = 0;

void setup() {
    Wire.begin(14, 12);
    display = Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET, OLED_CLK);
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) fatal(F("SSD1306 allocation failed")); display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setTextWrap(false);
    display.setRotation(OLED_ROTATION);
    display.clearDisplay();
    display.display();
}

template <typename T> inline void set_line(T text, uint8_t lineno) {
    if(lineno >= OLED_MAX_LINES) return;
    lines[lineno] = String(text);
}

template <typename T> inline void set_lines(T lines[], int n) {
    for(int i = 0; i < OLED_MAX_LINES; i++) {
        setLine(lines[i], i);
    }
}

inline void print_line(String &line, uint8_t lineno) {
    uint16_t w, a;
    int16_t b;
    display.getTextBounds(line, 0, 0, &b, &b, &w, &a);
    if(w > OLED_WIDTH) {
        display.setCursor(OLED_WIDTH - (scroll % (OLED_WIDTH + w)), lineno * OLED_LINE_HEIGHT);
    } else {
        display.setCursor(0, lineno * OLED_LINE_HEIGHT);
    }
    display.println(line);
}

void loop() {
    display.clearDisplay();
    for(uint8_t i = 0; i < OLED_MAX_LINES; i++) {
        print_line(lines[i], i);
    }
    display.display();
    unsigned long t = millis();
    uint16_t scroll_step = (t - last_scroll_update) * OLED_LINE_SCROLL_SPEED / 1000;
    if(scroll_step > 0) {
        scroll += scroll_step;
        last_scroll_update = t;
    }
}


}  // namespace screen




#else // OLED_INFO

namespace screen {
inline void setup() {}
template <typename T> inline void set_line(T text, uint8_t lineno) {}
template <typename T> inline void set_lines(T lines[], int n) {}
inline void loop() {}

}  // namespace screen

#endif // ! OLED_INFO
