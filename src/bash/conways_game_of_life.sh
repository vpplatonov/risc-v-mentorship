#!/usr/bin/env bash

# Animated Conway's Game of Life demonstration in Bash.
# The next_generation function shows iteration over a grid and Conway's rules.

set -u

PATTERN="glider"
WIDTH=30
HEIGHT=15
GENERATIONS=40
DELAY=0.15
NO_CLEAR=0
LIVE_CELLS=""

usage() {
  cat <<'EOF'
Usage: bash src/bash/conways_game_of_life.sh [options]

Options:
  --pattern NAME       Pattern: beacon, blinker, glider, or toad (default: glider)
  --width N            Grid width (default: 30)
  --height N           Grid height (default: 15)
  --generations N      Number of generations to display (default: 40)
  --delay SECONDS      Seconds to pause between generations (default: 0.15)
  --no-clear           Print each generation below the previous one
  -h, --help           Show this help message
EOF
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --pattern)
      PATTERN="$2"
      shift 2
      ;;
    --width)
      WIDTH="$2"
      shift 2
      ;;
    --height)
      HEIGHT="$2"
      shift 2
      ;;
    --generations)
      GENERATIONS="$2"
      shift 2
      ;;
    --delay)
      DELAY="$2"
      shift 2
      ;;
    --no-clear)
      NO_CLEAR=1
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "Unknown option: $1" >&2
      usage >&2
      exit 1
      ;;
  esac
done

require_number() {
  local name="$1"
  local value="$2"
  case "$value" in
    ''|*[!0-9]*)
      echo "$name must be a non-negative integer." >&2
      exit 1
      ;;
  esac
}

require_number "width" "$WIDTH"
require_number "height" "$HEIGHT"
require_number "generations" "$GENERATIONS"

if [ "$WIDTH" -lt 5 ] || [ "$HEIGHT" -lt 5 ]; then
  echo "Please use a grid at least 5 by 5." >&2
  exit 1
fi

clear_screen() {
  if [ "$NO_CLEAR" -eq 0 ]; then
    printf '\033[2J\033[H'
  fi
}

has_cell() {
  local x="$1"
  local y="$2"
  case " $LIVE_CELLS " in
    *" ${x},${y} "*) return 0 ;;
    *) return 1 ;;
  esac
}

add_cell() {
  local x="$1"
  local y="$2"
  LIVE_CELLS="${LIVE_CELLS}${x},${y} "
}

seed_pattern() {
  local pattern_width=0
  local pattern_height=0
  local coords=""
  local offset_x
  local offset_y
  local pair
  local x
  local y

  case "$PATTERN" in
    glider)
      pattern_width=3
      pattern_height=3
      coords="1,0 2,1 0,2 1,2 2,2"
      ;;
    blinker)
      pattern_width=3
      pattern_height=3
      coords="1,0 1,1 1,2"
      ;;
    toad)
      pattern_width=5
      pattern_height=3
      coords="2,1 3,1 4,1 1,2 2,2 3,2"
      ;;
    beacon)
      pattern_width=5
      pattern_height=5
      coords="1,1 2,1 1,2 4,3 3,4 4,4"
      ;;
    *)
      echo "Unknown pattern: $PATTERN" >&2
      echo "Supported patterns: beacon, blinker, glider, toad" >&2
      exit 1
      ;;
  esac

  offset_x=$(((WIDTH - pattern_width) / 2))
  offset_y=$(((HEIGHT - pattern_height) / 2))
  if [ "$offset_x" -lt 0 ]; then offset_x=0; fi
  if [ "$offset_y" -lt 0 ]; then offset_y=0; fi

  LIVE_CELLS=""
  for pair in $coords; do
    x="${pair%,*}"
    y="${pair#*,}"
    add_cell "$((x + offset_x))" "$((y + offset_y))"
  done
}

count_live_cells() {
  local total=0
  local pair
  for pair in $LIVE_CELLS; do
    total=$((total + 1))
  done
  printf '%s' "$total"
}

count_live_neighbors() {
  local x="$1"
  local y="$2"
  local total=0
  local dx
  local dy

  # Iteration demonstration: these nested loops visit the eight neighboring
  # coordinates around one cell and count how many are alive.
  for dy in -1 0 1; do
    for dx in -1 0 1; do
      if [ "$dx" -eq 0 ] && [ "$dy" -eq 0 ]; then
        continue
      fi
      if has_cell "$((x + dx))" "$((y + dy))"; then
        total=$((total + 1))
      fi
    done
  done

  printf '%s' "$total"
}

next_generation() {
  local next_cells=""
  local x
  local y
  local neighbors

  # Iteration demonstration: each generation is one complete pass over the
  # grid. Live cells survive with 2 or 3 neighbors, and dead cells are born with
  # exactly 3 neighbors.
  for ((y = 0; y < HEIGHT; y++)); do
    for ((x = 0; x < WIDTH; x++)); do
      neighbors="$(count_live_neighbors "$x" "$y")"
      if has_cell "$x" "$y"; then
        if [ "$neighbors" -eq 2 ] || [ "$neighbors" -eq 3 ]; then
          next_cells="${next_cells}${x},${y} "
        fi
      elif [ "$neighbors" -eq 3 ]; then
        next_cells="${next_cells}${x},${y} "
      fi
    done
  done

  LIVE_CELLS="$next_cells"
}

draw() {
  local generation="$1"
  local x
  local y

  clear_screen
  printf "Conway's Game of Life | generation: %s | live cells: %s\n" \
    "$generation" "$(count_live_cells)"
  printf '+'
  for ((x = 0; x < WIDTH; x++)); do printf '-'; done
  printf '+\n'

  for ((y = 0; y < HEIGHT; y++)); do
    printf '|'
    for ((x = 0; x < WIDTH; x++)); do
      if has_cell "$x" "$y"; then
        printf '#'
      else
        printf '.'
      fi
    done
    printf '|\n'
  done

  printf '+'
  for ((x = 0; x < WIDTH; x++)); do printf '-'; done
  printf '+\n'
  sleep "$DELAY"
}

seed_pattern

for ((generation = 0; generation <= GENERATIONS; generation++)); do
  draw "$generation"
  next_generation
done
