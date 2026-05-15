#!/usr/bin/env python3
import sys
import time

# =====================================================================
# 1. TOWER OF HANOI (Demonstrating Pure RECURSION)
# =====================================================================
def print_hanoi_state(pegs, total_disks):
    """Renders the state using standard safe ANSI escape codes."""
    print("\033[H\033[J", end="") # Safe clear screens without TERM var dependency
    print("--- TOWER OF HANOI (RECURSION ENGINE) ---")
    for level in range(total_disks - 1, -1, -1):
        row_str = "  "
        for p in range(3):
            if level < len(pegs[p]):
                disk_size = pegs[p][level]
                disk_graphic = ("=" * (disk_size * 2)).center(total_disks * 2)
                row_str += f"[{disk_graphic}]"
            else:
                row_str += "|".center(total_disks * 2 + 2)
            row_str += "    "
        print(row_str)
    print("=" * (total_disks * 8 + 6))
    print("      Peg A            Peg B            Peg C\n")
    time.sleep(0.5)

def move_hanoi(n, source, target, auxiliary, pegs, total_disks):
    """[EVALUATION NOTE: RECURSIVE ENGINE] Mathematical induction handler."""
    if n == 1:
        disk = pegs[source].pop()
        pegs[target].append(disk)
        print_hanoi_state(pegs, total_disks)
        return
    move_hanoi(n - 1, source, auxiliary, target, pegs, total_disks)
    disk = pegs[source].pop()
    pegs[target].append(disk)
    print_hanoi_state(pegs, total_disks)
    move_hanoi(n - 1, auxiliary, target, source, pegs, total_disks)


# =====================================================================
# 2. CONWAY'S GAME OF LIFE (Demonstrating Pure ITERATION)
# =====================================================================
def count_neighbors(grid, r, c, rows, cols):
    count = 0
    for i in [-1, 0, 1]:
        for j in [-1, 0, 1]:
            if i == 0 and j == 0:
                continue
            nr, nc = r + i, c + j
            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                count += 1
    return count

def run_conway_life(generations=10, rows=10, cols=24):
    """[EVALUATION NOTE: ITERATIVE ENGINE] Double nested loop framework."""
    grid = [[0] * cols for _ in range(rows)]
    # Glider seed
    grid[1][2] = grid[2][3] = grid[3][1] = grid[3][2] = grid[3][3] = 1

    for gen in range(generations):
        print("\033[H\033[J", end="")
        print(f"--- CONWAY'S GAME OF LIFE (ITERATIVE MATRIX) - GEN {gen+1}/{generations} ---")
        for r in range(rows):
            line = "".join(["#" if grid[r][c] == 1 else " " for c in range(cols)])
            print(f"  {line}")
        print("=" * (cols + 4))
        time.sleep(0.3)

        next_grid = [[0] * cols for _ in range(rows)]
        for r in range(rows):
            for c in range(cols):
                neighbors = count_neighbors(grid, r, c, rows, cols)
                if grid[r][c] == 1 and neighbors in [2, 3]:
                    next_grid[r][c] = 1
                elif grid[r][c] == 0 and neighbors == 3:
                    next_grid[r][c] = 1
        grid = next_grid


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "conway":
        run_conway_life()
    else:
        disks = 4
        move_hanoi(disks, 0, 2, 1, [list(range(disks, 0, -1)), [], []], disks)
