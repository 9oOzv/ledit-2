#include "main.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include "info.h"
#include "wifi.h"

Adafruit_NeoPixel pixels(40, 5, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(40, 4, NEO_RGB + NEO_KHZ800);
uint16_t i = 0;

void setup() {
    info::setup();
    wifi::setup();
    pixels.begin();
    pixels2.begin();
}


void loop() {
    info::line(String("millis: ") + millis(), 0);
    info::line(String("micros: ") + micros(), 1);
    info::line(String("random: ") + random(0, 100), 2);
    info::loop();
    i = (i + 1) % 40;
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(255, 0, 255));
    pixels.show();
    pixels2.clear();
    pixels2.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels2.show();
}
