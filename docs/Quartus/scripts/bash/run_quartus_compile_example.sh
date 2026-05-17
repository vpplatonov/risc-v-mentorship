#!/usr/bin/env bash
set -euo pipefail

# Usage:
#   ./run_quartus_compile_example.sh <top_entity>

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <top_entity>" >&2
  exit 1
fi

TOP_ENTITY="$1"
quartus_sh --flow compile "${TOP_ENTITY}"

