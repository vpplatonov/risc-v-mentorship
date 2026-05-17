#!/usr/bin/env bash
set -euo pipefail

export QUARTUS_ROOT="${QUARTUS_ROOT:-$HOME/altera_lite/25.1std}"
export QUARTUS_BIN="${QUARTUS_ROOT}/quartus/bin"
export QUARTUS_LIB="${QUARTUS_ROOT}/quartus/linux64"
export BRIDGED_LIB="${QUARTUS_LIB}/libccl_sqlite3.so"

# X11/ICE stability
export SESSION_MANAGER=""
export hostname="localhost"
export DISPLAY="${DISPLAY:-:0}"
export QT_X11_NO_MITSHM=1

# Java stability for Rosetta environments
export JAVA_TOOL_OPTIONS="-Xint -Xss2m -XX:-UseCompressedOops"
export _JAVA_OPTIONS="-Dsun.java2d.opengl=false -Dsun.java2d.xrender=false"

# MKL compatibility hints
export MKL_DEBUG_CPU_TYPE=5
export MKL_CBWR=SSE4_2

# Preload bridge if available
if [[ -f "${BRIDGED_LIB}" ]]; then
  export LD_PRELOAD="${BRIDGED_LIB}"
fi

# Restart daemon safely
pkill -9 jtagd >/dev/null 2>&1 || true
"${QUARTUS_BIN}/jtagd" >/dev/null 2>&1 &

exec "${QUARTUS_BIN}/quartus"

