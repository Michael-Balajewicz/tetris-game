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

## Design patterns

**Observer** — `src/core/abstract.cc` defines `Subject` and `Observer`. Each
`Board` *is a* `Subject`; the single `TextDisplay` *is an* `Observer` watching
both boards. `Board` calls `notify()` whenever it places a block or clears
lines, and `Game` wires the two together with `p1.getBoard().attach(&td)`. The
boards never know a display exists — swapping in a graphical view would touch
no board code.

**Strategy** — `Level` is an abstract base whose `createBlock()` defines *how*
the next block is chosen. `Level0` replays a scripted sequence from a file;
`Level1`–`Level3` use progressively harsher random distributions. `Player`
holds a `unique_ptr<Level>` and **swaps it at runtime** in `levelUp()` /
`levelDown()`, so difficulty changes mid-game without any other Player code
changing.

**Factory Method** — `Level::createBlock()` is the factory method itself: the
base class declares it, and each concrete level decides which `Block` to
return.

**Factory functions** — `makeBlock()` maps a `BlockType` to its four cell
offsets; `makeLevel()` / `makeLevel0()` construct levels. `Level0`–`Level3`
are deliberately *not* exported from the `Level` module, so these functions are
the only way to build one — the module boundary enforces the encapsulation that
a header-based design would need a separate `.h`/`.cc` split to achieve.

Note that `CommandInterpreter` is a *parser*, not the Command pattern: it turns
a line of input into a `CommandType` enum plus a repeat count, which
`Game::run()` dispatches through an if/else chain.
