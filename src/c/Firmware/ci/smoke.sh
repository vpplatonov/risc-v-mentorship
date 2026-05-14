#!/usr/bin/env bash
set -euo pipefail

echo "smoke: build firmware scaffold"
make -C ../firmware
