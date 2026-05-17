#!/usr/bin/env bash
set -euo pipefail

QUARTUS_LINUX64_DIR="${1:-$HOME/altera_lite/25.1std/quartus/linux64}"
SRC_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

echo "Building bridge library into: ${QUARTUS_LINUX64_DIR}"
gcc -shared -fPIC -O2 -Wall -Wextra \
  -o "${QUARTUS_LINUX64_DIR}/libccl_sqlite3.so" \
  "${SRC_DIR}/c/altr_sqlite_bridge.c" \
  -ldl

echo "Bridge built: ${QUARTUS_LINUX64_DIR}/libccl_sqlite3.so"

