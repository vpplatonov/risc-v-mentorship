#!/usr/bin/env bash

# Animated Tower of Hanoi demonstration in Bash.
# The recursive solve_hanoi function is the main programming concept shown here.

set -u

DISKS=4
DELAY=0.35
NO_CLEAR=0
MOVE_COUNT=0
POPPED_DISK=""
PEG_A=()
PEG_B=()
PEG_C=()

usage() {
  cat <<'EOF'
Usage: bash src/bash/tower_of_hanoi.sh [options]

Options:
  -n, --disks N     Number of disks, from 1 to 8 (default: 4)
  --delay SECONDS   Seconds to pause between moves (default: 0.35)
  --no-clear        Print each state below the previous one
  -h, --help        Show this help message
EOF
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    -n|--disks)
      DISKS="$2"
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

case "$DISKS" in
  ''|*[!0-9]*)
    echo "Please choose a disk count from 1 to 8." >&2
    exit 1
    ;;
esac

if [ "$DISKS" -lt 1 ] || [ "$DISKS" -gt 8 ]; then
  echo "Please choose a disk count from 1 to 8." >&2
  exit 1
fi

clear_screen() {
  if [ "$NO_CLEAR" -eq 0 ]; then
    printf '\033[2J\033[H'
  fi
}

repeat_char() {
  local char="$1"
  local count="$2"
  local result=""
  local i
  for ((i = 0; i < count; i++)); do
    result="${result}${char}"
  done
  printf '%s' "$result"
}

center_text() {
  local text="$1"
  local width="$2"
  local pad=$((width - ${#text}))
  local left=$((pad / 2))
  local right=$((pad - left))
  repeat_char " " "$left"
  printf '%s' "$text"
  repeat_char " " "$right"
}

get_disk() {
  local peg="$1"
  local level="$2"
  local value=0
  case "$peg" in
    A)
      if [ "$level" -lt "${#PEG_A[@]}" ]; then value="${PEG_A[$level]}"; fi
      ;;
    B)
      if [ "$level" -lt "${#PEG_B[@]}" ]; then value="${PEG_B[$level]}"; fi
      ;;
    C)
      if [ "$level" -lt "${#PEG_C[@]}" ]; then value="${PEG_C[$level]}"; fi
      ;;
  esac
  printf '%s' "$value"
}

render_disk() {
  local size="$1"
  local width=$((DISKS * 2 - 1))
  local disk="|"
  if [ "$size" -gt 0 ]; then
    disk="$(repeat_char "=" "$((size * 2 - 1))")"
  fi
  center_text "$disk" "$width"
}

draw() {
  local level
  local peg
  local disk
  local width=$((DISKS * 2 - 1))

  clear_screen
  printf 'Tower of Hanoi | disks: %s | moves: %s\n\n' "$DISKS" "$MOVE_COUNT"
  for ((level = DISKS - 1; level >= 0; level--)); do
    for peg in A B C; do
      disk="$(get_disk "$peg" "$level")"
      render_disk "$disk"
      if [ "$peg" != "C" ]; then printf '   '; fi
    done
    printf '\n'
  done
  for peg in A B C; do
    repeat_char "-" "$width"
    if [ "$peg" != "C" ]; then printf '   '; fi
  done
  printf '\n'
  center_text "A" "$width"; printf '   '
  center_text "B" "$width"; printf '   '
  center_text "C" "$width"; printf '\n'
  sleep "$DELAY"
}

pop_disk() {
  local peg="$1"
  case "$peg" in
    A)
      POPPED_DISK="${PEG_A[$((${#PEG_A[@]} - 1))]}"
      unset "PEG_A[$((${#PEG_A[@]} - 1))]"
      ;;
    B)
      POPPED_DISK="${PEG_B[$((${#PEG_B[@]} - 1))]}"
      unset "PEG_B[$((${#PEG_B[@]} - 1))]"
      ;;
    C)
      POPPED_DISK="${PEG_C[$((${#PEG_C[@]} - 1))]}"
      unset "PEG_C[$((${#PEG_C[@]} - 1))]"
      ;;
  esac
}

push_disk() {
  local peg="$1"
  local value="$2"
  case "$peg" in
    A) PEG_A[${#PEG_A[@]}]="$value" ;;
    B) PEG_B[${#PEG_B[@]}]="$value" ;;
    C) PEG_C[${#PEG_C[@]}]="$value" ;;
  esac
}

move_disk() {
  local source="$1"
  local target="$2"
  pop_disk "$source"
  push_disk "$target" "$POPPED_DISK"
  MOVE_COUNT=$((MOVE_COUNT + 1))
}

solve_hanoi() {
  local disk_count="$1"
  local source="$2"
  local target="$3"
  local spare="$4"

  # Recursion demonstration:
  # Base case: if there are no disks to move, return.
  # Recursive case: move the smaller stack, move one disk, then move the stack
  # again onto the target peg.
  if [ "$disk_count" -eq 0 ]; then
    return
  fi

  solve_hanoi "$((disk_count - 1))" "$source" "$spare" "$target"
  move_disk "$source" "$target"
  draw
  solve_hanoi "$((disk_count - 1))" "$spare" "$target" "$source"
}

for ((disk = DISKS; disk >= 1; disk--)); do
  PEG_A[${#PEG_A[@]}]="$disk"
done

draw
solve_hanoi "$DISKS" A C B
printf '\nSolved in %s moves.\n' "$MOVE_COUNT"
