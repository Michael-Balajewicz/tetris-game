# Biquadris

A two-player, head-to-head Tetris variant for the terminal. Players alternate
turns on side-by-side boards; clearing lines fires special actions at your
opponent. Written in C++20 using **modules** (not headers).

## Requirements

- **g++ 14 or newer** — earlier versions crash on this project's module usage.
- GNU make

The `Makefile` calls `g++-14`. If your compiler is just `g++`, override it:

```bash
make CXX=g++
```

**On Windows/MSYS2:** build from the *UCRT64* shell, not Git Bash. Git Bash puts
its own `mingw64` runtime ahead of MSYS2's on `PATH`, which makes `cc1plus`
fail silently with no error message.

## Build & run

```bash
make
./biquadris
```

| Flag | Default | Meaning |
|---|---|---|
| `-seed N` | `1` | RNG seed for block generation |
| `-startlevel N` | `0` | Starting difficulty, `0`–`3` |
| `-scriptfile1 F` | `data/biquadris_sequence1.txt` | Level-0 block sequence, player 1 |
| `-scriptfile2 F` | `data/biquadris_sequence2.txt` | Level-0 block sequence, player 2 |

`make clean` removes `build/`, `gcm.cache/` and the binary.

## Commands

Typed at the prompt, one per line. Any unique prefix works (`le` = `left`), and
a leading number repeats the command (`3down`).

`left` `right` `down` `drop` `clockwise` `counterclockwise`
`levelup` `leveldown` `restart` `exit`

## Layout

```
src/
├── main.cc    argument parsing, entry point
├── core/      types (Point, BlockType), abstract (Observer pattern)
├── game/      block, board, level, score, player, game
└── ui/        textdisplay (the Observer), commandInterpreter
data/          level-0 block sequences
```

Each module is a pair: `foo.cc` declares the interface (`export module Foo;`),
`foo-impl.cc` implements it. Module names are independent of file paths, so
moving a file never breaks an `import`.
