#!/usr/bin/env python3
"""Animated Conway's Game of Life demonstration.

This script shows a small cellular automaton in the terminal. Each generation
is produced by iterating over the grid, counting live neighbors, and applying
Conway's rules to decide which cells live in the next generation.
"""

from __future__ import annotations

import argparse
import time


Grid = set[tuple[int, int]]


PATTERNS: dict[str, Grid] = {
    "glider": {
        (1, 0),
        (2, 1),
        (0, 2),
        (1, 2),
        (2, 2),
    },
    "blinker": {
        (1, 0),
        (1, 1),
        (1, 2),
    },
    "toad": {
        (2, 1),
        (3, 1),
        (4, 1),
        (1, 2),
        (2, 2),
        (3, 2),
    },
    "beacon": {
        (1, 1),
        (2, 1),
        (1, 2),
        (4, 3),
        (3, 4),
        (4, 4),
    },
}


def clear_screen(enabled: bool) -> None:
    if enabled:
        print("\033[2J\033[H", end="")


def seed_pattern(name: str, width: int, height: int) -> Grid:
    pattern = PATTERNS[name]
    pattern_width = max(x for x, _ in pattern) + 1
    pattern_height = max(y for _, y in pattern) + 1
    offset_x = max(0, (width - pattern_width) // 2)
    offset_y = max(0, (height - pattern_height) // 2)
    return {(x + offset_x, y + offset_y) for x, y in pattern}


def count_live_neighbors(live_cells: Grid, x: int, y: int) -> int:
    """Count live neighbors around one cell.

    Iteration demonstration: the nested loops visit the eight surrounding
    coordinates and accumulate how many of those coordinates are currently
    alive.
    """
    total = 0
    for dy in (-1, 0, 1):
        for dx in (-1, 0, 1):
            if dx == 0 and dy == 0:
                continue
            if (x + dx, y + dy) in live_cells:
                total += 1
    return total


def next_generation(live_cells: Grid, width: int, height: int) -> Grid:
    """Build the next grid by applying Conway's rules to every cell.

    Iteration demonstration: each generation is a complete pass over the grid.
    A live cell survives with 2 or 3 neighbors. A dead cell is born with exactly
    3 neighbors. All other cells are absent from the next generation.
    """
    next_cells: Grid = set()
    for y in range(height):
        for x in range(width):
            neighbors = count_live_neighbors(live_cells, x, y)
            is_alive = (x, y) in live_cells
            if is_alive and neighbors in (2, 3):
                next_cells.add((x, y))
            elif not is_alive and neighbors == 3:
                next_cells.add((x, y))
    return next_cells


def render(live_cells: Grid, width: int, height: int, generation: int) -> str:
    lines = [
        f"Conway's Game of Life | generation: {generation} | live cells: {len(live_cells)}",
        "+" + "-" * width + "+",
    ]
    for y in range(height):
        row = []
        for x in range(width):
            row.append("#" if (x, y) in live_cells else ".")
        lines.append("|" + "".join(row) + "|")
    lines.append("+" + "-" * width + "+")
    return "\n".join(lines)


def draw(
    live_cells: Grid,
    width: int,
    height: int,
    generation: int,
    delay: float,
    animate: bool,
) -> None:
    clear_screen(animate)
    print(render(live_cells, width, height, generation))
    if delay > 0:
        time.sleep(delay)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Render Conway's Game of Life in the terminal."
    )
    parser.add_argument(
        "--pattern",
        choices=sorted(PATTERNS),
        default="glider",
        help="starting pattern to place near the center of the grid",
    )
    parser.add_argument("--width", type=int, default=30, help="grid width")
    parser.add_argument("--height", type=int, default=15, help="grid height")
    parser.add_argument(
        "--generations",
        type=int,
        default=40,
        help="number of generations to display",
    )
    parser.add_argument(
        "--delay",
        type=float,
        default=0.15,
        help="seconds to pause between generations",
    )
    parser.add_argument(
        "--no-clear",
        action="store_true",
        help="print each generation below the previous one instead of animating in place",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    if args.width < 5 or args.height < 5:
        raise SystemExit("Please use a grid at least 5 by 5.")
    if args.generations < 0:
        raise SystemExit("Generation count cannot be negative.")
    if args.delay < 0:
        raise SystemExit("Delay cannot be negative.")

    live_cells = seed_pattern(args.pattern, args.width, args.height)
    animate = not args.no_clear

    for generation in range(args.generations + 1):
        draw(live_cells, args.width, args.height, generation, args.delay, animate)
        live_cells = next_generation(live_cells, args.width, args.height)


if __name__ == "__main__":
    main()
