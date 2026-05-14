#!/usr/bin/env python3
"""Animated Tower of Hanoi demonstration.

This script solves the Tower of Hanoi puzzle and prints each board state with
simple ASCII graphics. The recursive solver is intentionally kept visible and
commented because that is the central programming concept being demonstrated.
"""

from __future__ import annotations

import argparse
import time
from dataclasses import dataclass


PEG_NAMES = ("A", "B", "C")


@dataclass
class HanoiState:
    pegs: dict[str, list[int]]
    move_count: int = 0


def clear_screen(enabled: bool) -> None:
    if enabled:
        print("\033[2J\033[H", end="")


def render_disk(size: int, max_size: int) -> str:
    if size == 0:
        disk = "|"
    else:
        disk = "=" * (size * 2 - 1)
    return disk.center(max_size * 2 - 1)


def render(state: HanoiState, disk_count: int) -> str:
    lines = [f"Tower of Hanoi | disks: {disk_count} | moves: {state.move_count}"]
    lines.append("")

    for level in range(disk_count - 1, -1, -1):
        parts = []
        for peg in PEG_NAMES:
            disk = state.pegs[peg][level] if level < len(state.pegs[peg]) else 0
            parts.append(render_disk(disk, disk_count))
        lines.append("   ".join(parts))

    base_width = disk_count * 2 - 1
    lines.append("   ".join("-" * base_width for _ in PEG_NAMES))
    lines.append("   ".join(name.center(base_width) for name in PEG_NAMES))
    return "\n".join(lines)


def draw(state: HanoiState, disk_count: int, delay: float, animate: bool) -> None:
    clear_screen(animate)
    print(render(state, disk_count))
    if delay > 0:
        time.sleep(delay)


def move_disk(state: HanoiState, source: str, target: str) -> None:
    disk = state.pegs[source].pop()
    state.pegs[target].append(disk)
    state.move_count += 1


def solve_hanoi(
    disk_count: int,
    source: str,
    target: str,
    spare: str,
    state: HanoiState,
    delay: float,
    animate: bool,
) -> None:
    """Move disk_count disks from source to target.

    Recursion demonstration:
    1. Move the smaller stack out of the way.
    2. Move the largest remaining disk to the target peg.
    3. Move the smaller stack onto that largest disk.

    The base case is disk_count == 0: there is no disk to move, so the function
    returns without making another recursive call.
    """
    if disk_count == 0:
        return

    solve_hanoi(disk_count - 1, source, spare, target, state, delay, animate)
    move_disk(state, source, target)
    draw(state, sum(len(disks) for disks in state.pegs.values()), delay, animate)
    solve_hanoi(disk_count - 1, spare, target, source, state, delay, animate)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Render and solve the Tower of Hanoi puzzle in the terminal."
    )
    parser.add_argument(
        "-n",
        "--disks",
        type=int,
        default=4,
        help="number of disks to solve, from 1 to 8 (default: 4)",
    )
    parser.add_argument(
        "--delay",
        type=float,
        default=0.35,
        help="seconds to pause between moves (default: 0.35)",
    )
    parser.add_argument(
        "--no-clear",
        action="store_true",
        help="print each state below the previous one instead of animating in place",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    if not 1 <= args.disks <= 8:
        raise SystemExit("Please choose a disk count from 1 to 8.")
    if args.delay < 0:
        raise SystemExit("Delay cannot be negative.")

    state = HanoiState(
        pegs={
            "A": list(range(args.disks, 0, -1)),
            "B": [],
            "C": [],
        }
    )

    animate = not args.no_clear
    draw(state, args.disks, args.delay, animate)
    solve_hanoi(args.disks, "A", "C", "B", state, args.delay, animate)
    print(f"\nSolved in {state.move_count} moves.")


if __name__ == "__main__":
    main()
