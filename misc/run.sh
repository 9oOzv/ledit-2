#!/usr/bin/env bash
set -euo pipefail
shopt -s inherit_errexit
script_dir="$(dirname "$0")"
. "$script_dir"/config.sh
build_flags=(
    ${DEBUG:+-DDEBUG}
    ${SERIAL_INFO:+-DSERIAL_INFO}
    ${OLED_INFO:+-DOLED_INFO}
    ${WIFI_SSID:+-DWIFI_SSID=\"$WIFI_SSID\"}
    ${WIFI_PASSWORD:+-DWIFI_PASSWORD=\"$WIFI_PASSWORD\"}
)

set -x
arduino-cli board attach -b "$FQBN" -p "$PORT" "$SKETCH" 
arduino-cli compile "$SKETCH" -b "$FQBN" --build-property build.extra_flags="${build_flags[*]}"
arduino-cli upload "$SKETCH"
