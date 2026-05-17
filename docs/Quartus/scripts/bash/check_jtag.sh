#!/usr/bin/env bash
set -euo pipefail

QUARTUS_ROOT="${QUARTUS_ROOT:-$HOME/altera_lite/25.1std}"
"${QUARTUS_ROOT}/quartus/bin/jtagconfig"

