# Ice Sliding Puzzle

A C++ implementation of the "ice sliding" puzzle, where a flamingo slides across a
frozen grid until it hits a rock or the edge, and the goal is to bring it to rest on
the rescue cell. The project has two parts, each a standalone CMake program with its
own GoogleTest suite:

- **`player/`** — an interactive version you play from the terminal.
- **`solver/`** — an automatic solver that finds the shortest rescue path using
  breadth-first and depth-first search.

Both were written for the Imperative Programming course (Radboud University, year 2).

## The puzzle

The grid uses these cells:

| Symbol | Meaning                                       |
|:------:|-----------------------------------------------|
| `.`    | ice — the flamingo slides across it           |
| `r`    | rock — stops the flamingo's slide             |
| `x`    | rescue cell — the goal                        |
| `f`    | flamingo                                      |
| `F`    | flamingo resting on the rescue cell (solved)  |

When the flamingo moves in a direction it keeps sliding until the next cell is a rock,
it reaches the rescue cell, or it runs off the edge of the grid — in which case it
falls into the water. The grid edges are **not** walls.

## Building

You need CMake (3.10+) and a C++20 compiler. GoogleTest is downloaded automatically by
CMake on the first configure, so an internet connection is needed the first time.

From the repository root, a single command builds **both** parts at once:

```sh
cmake -B build
cmake --build build
```

This produces four executables:

| Executable                  | What it is                         |
|-----------------------------|------------------------------------|
| `build/player/main`         | the interactive game               |
| `build/player/main_test`    | the player's test suite (14 tests) |
| `build/solver/main`         | the BFS/DFS solver                 |
| `build/solver/main_test`    | the solver's test suite (21 tests) |

The example puzzles in each `files/` folder are copied next to the matching executable
during the build.

## Running

### Play the game (player)

```sh
cd build/player
./main
```

At the `Enter file to open:` prompt, type a puzzle name, e.g. `challenge.1.3steps.txt`.
Then play move by move:

```
'n' / 'e' / 's' / 'w'   slide north / east / south / west
'r'                      reset to the start
'q'                      quit
```

It counts your steps, restarts the level if the flamingo drowns, and tells you when the
flamingo reaches the rescue cell.

### Solve a puzzle (solver)

```sh
cd build/solver
./main
```

Enter a puzzle name at the prompt, then choose an algorithm when asked:

- `bfs` — breadth-first search; always returns the **minimum** number of moves.
- `dfs` — depth-first search with backtracking and pruning; you can also give it a
  depth limit (`-1` for no limit).

The solver prints each board state along the solution and the number of steps, or
reports that the puzzle has no solution / an invalid format.

> **Note on file paths.** The puzzle files are copied next to each `main`, so when you
> run from inside `build/player` or `build/solver` you can type just the file name
> (`challenge.1.3steps.txt`). If you instead run from the repository root
> (`./build/player/main`), give the path including the folder:
> `files/challenge.1.3steps.txt`.

## Testing

Each part has its own GoogleTest suite. Run them directly:

```sh
./build/player/main_test     # 14 tests
./build/solver/main_test     # 21 tests
```

Or let CTest run everything from the build directory:

```sh
cd build
ctest --output-on-failure
```

## Layout

```
Ice-Sliding-Puzzle/
├── CMakeLists.txt       top-level build (pulls in both parts)
├── README.md
├── .gitignore
├── player/              interactive game (assignment 13)
│   ├── main.cpp
│   ├── main_test.cpp
│   ├── CMakeLists.txt
│   └── files/           example puzzles
└── solver/              BFS/DFS solver (assignment 14)
    ├── main.cpp
    ├── main_test.cpp
    ├── CMakeLists.txt
    └── files/           example puzzles
```
