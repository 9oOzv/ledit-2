#!/usr/bin/env bash
script_dir="$(dirname "$0")"
set -euo pipefail
shopt -s inherit_errexit

sudo cp "$script_dir/99-esp8266.rules" "/etc/udev/rules.d"
sudo udevadm control --reload
sudo udevadm trigger

