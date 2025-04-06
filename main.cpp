#include "main.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include "info.h"
#include "wifi.h"
#include "effects/static.h"
#include "effects/rainbow.h"
#include "common.h"

Adafruit_NeoPixel pixels1(40, 5, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(40, 4, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(40, 0, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(40, 2, NEO_RGB + NEO_KHZ800);
uint16_t i = 0;
effect::Rainbow rainbow_effect(1);
effect::Static static_effect(0xFFFFFF);

effect::Effect *effects[] = {
    &rainbow_effect,
    &static_effect,
};
uint8_t i_current_effect = 0;
uint32_t colors[40];

void setup() {
    info::setup();
    wifi::setup();
    pixels1.begin();
    pixels2.begin();
    pixels3.begin();
    pixels4.begin();
}

template<uint16_t N>
inline void setPixels(Adafruit_NeoPixel &pixels, uint32_t (&colors)[N]) {
    pixels.clear();
    for(uint16_t i = 0; i < N; i++) {
        pixels.setPixelColor(i, colors[i]);
    }
    pixels.show();
}

void choose_effect(uint16_t i) {
    i = i % arrsize(effects);
    info::debug(String("choose effect: ") + i);
    i_current_effect = i;
}

void loop_wifi() {
    char data[33];
    wifi::read_package(data);
    // First byte in data is the effect
    // Next 20 bytes are 10 uint16_t parameters for the effect
    uint8_t effect = static_cast<uint8_t>(data[0]);
    uint16_t params[16];
    memcpy(params, data+1, 32);
    if(effect == 0)
        return;
    info::debug(
        String("remote command: ")
        + effect
        + " " + join(params, ",", HEX)
    );
    choose_effect(effect-1);
    effect::Effect &eff = *effects[i_current_effect];
    eff.set_parameters(params);
}

void loop() {
    loop_wifi();
    effect::Effect &eff = *effects[i_current_effect];
    eff.apply(colors, colors);
    i = (i + 1) % 40;
    setPixels(pixels1, colors);
    setPixels(pixels2, colors);
    setPixels(pixels3, colors);
    setPixels(pixels4, colors);
    info::line(String("millis: ") + millis(), 0);
    info::line(String("micros: ") + micros(), 1);
    info::line(String("random: ") + random(0, 100), 2);
    info::loop();
}
