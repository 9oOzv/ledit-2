#!/usr/bin/env bash
set -euo pipefail
shopt -s inherit_errexit
script_dir="$(dirname "$0")"
. "$script_dir"/config.sh
build_flags=(
    ${DEBUG:+-DDEBUG}
    ${SERIAL_INFO:+-DSERIAL_INFO}
    ${OLED_INFO:+-DOLED_INFO}
)

set -x
arduino-cli board attach -b "$FQBN" -p "$PORT" "$SKETCH" 
arduino-cli compile "$SKETCH" -b "$FQBN" --build-property build.extra_flags="${build_flags[*]}"
arduino-cli upload "$SKETCH"
