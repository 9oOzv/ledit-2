#!/usr/bin/env bash
set -euo pipefail
shopt -s inherit_errexit

# Install esp8266 boards
arduino-cli core --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json install esp8266:esp8266
arduino-cli lib install "Adafruit SSD1306"
arduino-cli lib install "Adafruit GFX Library"
arduino-cli lib install "Adafruit NeoPixel"
