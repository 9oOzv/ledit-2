#include "main.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include "info.h"

Adafruit_NeoPixel pixels(200, 5, NEO_RGB + NEO_KHZ800);
uint16_t i = 0;

void setup() {
    info::setup();
    pixels.begin();
}


void loop() {
    info::line(String("millis: ") + millis(), 0);
    info::line(String("micros: ") + micros(), 1);
    info::line(String("random: ") + random(0, 100), 2);
    info::line("FOO BAR", 3);
    info::line("BAZZFIZZBIZZBAZZFAZZFIZZFUZZFUCK", 4);
    info::line("BUZZ", 5);
    info::line("FUCK", 6);
    info::loop();
    i = (i + 1) % 200;
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(255, 0, 255));
    pixels.show();
}
