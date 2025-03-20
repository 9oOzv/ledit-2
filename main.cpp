#include "main.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "info.h"
#include "serial.h"



void setup() {
    serial::setup();
    serial::line("Hello, world!\n");
    info::setup();
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
    delay(10);
}
