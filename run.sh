#!/usr/bin/env bash
set -euo pipefail
shopt -s inherit_errexit
script_dir="$(dirname "$0")"
. "$script_dir"/config.sh
build_flags=( ${DEBUG:+-DDEBUG} )
arduino-cli board attach -b "$FQBN" -p "$PORT"
arduino-cli compile -b "$FQBN" --build-property build.extra_flags="${build_flags[@]}"
arduino-cli upload
