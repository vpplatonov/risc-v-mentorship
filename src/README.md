## Solutions

This project implements the two challenge options in Python and Bash:

- `python/tower_of_hanoi.py` renders each peg and disk using ASCII graphics.
- The recursive solver is in `solve_hanoi(...)`.
- The script comments identify the base case and the three recursive steps.
- `python/conways_game_of_life.py` renders a cellular automaton grid using
  ASCII graphics.
- The iteration logic is in `count_live_neighbors(...)` and
  `next_generation(...)`.
- The script comments identify the nested loops and Conway update rules.
- `bash/tower_of_hanoi.sh` solves Tower of Hanoi in Bash using recursive
  function calls.
- `bash/conways_game_of_life.sh` simulates Conway's Game of Life in Bash using
  nested loops over the grid.

## Run

Python Tower of Hanoi:

```bash
python3 src/python/tower_of_hanoi.py
```

Useful options:

```bash
python3 src/python/tower_of_hanoi.py --disks 3 --delay 0.2
python3 src/python/tower_of_hanoi.py --disks 4 --delay 0 --no-clear
```

`--no-clear` prints every board state one after another, which is useful when
reviewing the full sequence of moves.

Bash Tower of Hanoi:

```bash
bash src/bash/tower_of_hanoi.sh
```

Useful options:

```bash
bash src/bash/tower_of_hanoi.sh --disks 3 --delay 0.2
bash src/bash/tower_of_hanoi.sh --disks 4 --delay 0 --no-clear
```

Python Conway's Game of Life:

```bash
python3 src/python/conways_game_of_life.py
```

Useful options:

```bash
python3 src/python/conways_game_of_life.py --pattern glider --generations 20
python3 src/python/conways_game_of_life.py --pattern blinker --width 15 --height 9 --delay 0 --no-clear
```

Bash Conway's Game of Life:

```bash
bash src/bash/conways_game_of_life.sh
```

Useful options:

```bash
bash src/bash/conways_game_of_life.sh --pattern glider --generations 20
bash src/bash/conways_game_of_life.sh --pattern blinker --width 15 --height 9 --delay 0 --no-clear
```

Supported patterns are `beacon`, `blinker`, `glider`, and `toad`.
