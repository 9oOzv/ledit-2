#!/usr/bin/env bash
script_dir="$(dirname "$0")"
set -euo pipefail
shopt -s inherit_errexit
export DEBUG=1
export SERIAL_INFO=1
. "$script_dir"/config.sh
"$script_dir"/run.sh
arduino-cli monitor --config 115200 -p "$PORT"
