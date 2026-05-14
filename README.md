Coding Challenge - Broadening the RISC-V High Precision Code Base and Reach

Challenge prompt:

Please create a "Tower Of Hanoi" or "Conway's Game of Life" code demonstration
in a scripted language or bash script. This can be short, just enough to
demonstrate functionality with simple graphics. Ideally, you can identify and
comment on the sections that demonstrate recursion and / or iteration.
Optionally, place it on a publicly accessible github site.

## Game Descriptions

### Tower of Hanoi

Tower of Hanoi is a puzzle with three pegs and a stack of disks. The goal is to
move the full stack from the first peg to the last peg while following two
rules:

- Move only one disk at a time.
- Never place a larger disk on top of a smaller disk.

This puzzle is a natural recursion example. To move a stack, the program first
moves the smaller stack out of the way, then moves the largest disk, then moves
the smaller stack back on top of it. The script solves the puzzle and prints
each legal move as ASCII graphics.

### Conway's Game of Life

Conway's Game of Life is a cellular automaton played on a grid. Each cell is
either alive or dead, and the next generation is calculated from the current
generation using these rules:

- A live cell survives if it has 2 or 3 live neighbors.
- A dead cell becomes alive if it has exactly 3 live neighbors.
- All other cells are dead in the next generation.

This simulation is a natural iteration example. For each generation, the program
loops over the grid, counts the live neighbors around every cell, applies the
rules, and renders the next grid as ASCII graphics.

## Run

See `src/README.md`.
