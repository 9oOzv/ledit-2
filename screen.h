#pragma once
#include <Arduino.h>
#include "error.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C
#define OLED_CLK 800000UL
#define OLED_MAX_LINES 8
#define OLED_LINE_HEIGHT OLED_HEIGHT / OLED_MAX_LINES
#define OLED_ROTATION 2




#ifdef OLED_INFO

namespace screen {

Adafruit_SSD1306 display;
String lines[OLED_MAX_LINES];

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

template <typename T> void set_line(T text, uint8_t lineno) {
    if(lineno >= OLED_MAX_LINES) return;
    lines[lineno] = String(text);
}

template <typename T> void set_lines(T lines[], int n) {
    for(int i = 0; i < OLED_MAX_LINES; i++) {
        setLine(lines[i], i);
    }
}

void loop() {
    display.clearDisplay();
    for(int i = 0; i < OLED_MAX_LINES; i++) {
        display.setCursor(0, i * OLED_LINE_HEIGHT);
        display.println(lines[i]);
    }
    display.display();
}

}  // namespace screen




#else // OLED_INFO

namespace screen {
void setup() {}
template <typename T> void set_line(T text, uint8_t lineno) {}
template <typename T> void set_lines(T lines[], int n) {}
void loop() {}

}  // namespace screen

#endif // ! OLED_INFO
