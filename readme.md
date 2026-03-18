# Lux

A GPU-accelerated 2D rendering library with both CPU and GPU backends.

## Project Structure

```
shared/
├── lux.h               — public API (scenes, instructions, dispatch)
├── lux_priv.h           — private types (vtable, instruction buffer internals)
└── lux_priv.c           — shared implementation (instruction buffer, dispatch)
utilities/
├── cuda_helpers.h       — CUDA init, NVRTC compilation, cleanup
├── cuda_helpers.c
├── cuda_stubs/          — stubs for clang-based CUDA linting
└── stb/                 — vendored stb single-header image libraries
cpu/
├── lux_cpu.c            — CPU backend implementation
├── lux_cpu.h
└── dune
examples/
└── cpu-basic/
    ├── main.c           — CPU backend demo
    └── dune
gpu/
├── main.c               — GPU backend demo
├── kernel.cu            — GPU kernel (compiled at runtime via NVRTC)
└── dune
test/
├── imgdiff.sh           — image comparison script
├── test_harness.h       — shared test runner and dune.inc generator
├── draw_pixel/          — pixel rendering tests (expected/ has baselines)
└── draw_rect/           — rectangle rendering tests (expected/ has baselines)
```

## Design Decisions

**Runtime compilation with NVRTC instead of nvcc.** The host code is compiled
with plain `gcc`. The CUDA kernel source is kept in a separate `kernel.cu` file
which gets loaded as a string and compiled at runtime via NVRTC. This means the
edit-run cycle for kernel code doesn't require a recompile of the host program.

**CUDA Driver API instead of Runtime API.** Since we're using NVRTC to compile
kernels at runtime, we use the CUDA Driver API (`cuMemAlloc`, `cuLaunchKernel`,
etc.) rather than the Runtime API (`cudaMalloc`, `<<<>>>` syntax). The Driver API
gives explicit control over contexts, modules, and kernel launches, which pairs
naturally with runtime-compiled PTX.

**dune as the build system.** Each subdirectory has a `dune` file with custom
rules that invoke `gcc` directly. This keeps the build declarative and incremental
without needing CMake or Makefiles.

## Usage

```bash
# build and run the CPU backend
opam exec -- dune build @cpu/run

# build and run the GPU backend
opam exec -- dune build @gpu/run

# build a specific target
opam exec -- dune build examples/cpu-basic/main.exe
opam exec -- dune build gpu/main.exe
```

## Testing

Tests use a **check against expected / promote** workflow. Each test executable
produces PNG images which are compared against checked-in baselines in
`expected/` using ImageMagick (with a 1% fuzzy threshold via `test/imgdiff.sh`).

```
test/
├── imgdiff.sh              — image comparison script (requires ImageMagick)
├── test_harness.h          — shared test runner and dune.inc generator
├── draw_pixel/
│   ├── main.c              — pixel rendering tests
│   ├── dune                — compile, lint, and comparison rules
│   ├── dune.inc            — auto-generated comparison rules
│   ├── actual/             — latest outputs (auto-promoted by dune, gitignored)
│   └── expected/           — checked-in baselines
└── draw_rect/
    ├── main.c              — rectangle rendering tests
    ├── dune                — compile, lint, and comparison rules
    ├── dune.inc            — auto-generated comparison rules
    ├── actual/             — latest outputs (auto-promoted by dune, gitignored)
    └── expected/           — checked-in baselines
```

### Running tests

```bash
# run all tests
opam exec -- dune build @runtest

# run a specific test group
opam exec -- dune build @test/draw_pixel/runtest
opam exec -- dune build @test/draw_rect/runtest
```

When tests run, dune's `(mode promote)` automatically copies the generated
`.png` files into the source tree so you can inspect them directly.

### Updating baselines

If a rendering change is intentional and the new output looks correct:

```bash
# promote a single baseline
cp test/draw_pixel/actual/single_pixel.png test/draw_pixel/expected/

# or promote all baselines for a test group
cp test/draw_rect/actual/*.png test/draw_rect/expected/
```

Then re-run tests to confirm they pass.

### Adding a new test case

1. Add a new function in the relevant `main.c` (e.g. `test/draw_pixel/main.c`).
2. Add an entry to the `tests[]` array.
3. Run the tests with `--auto-promote` to regenerate the `dune.inc` files:
   ```bash
   opam exec -- dune build @runtest --auto-promote
   ```
   The build rules use a **diff workflow**: the test executable generates
   `dune.inc.gen` files which are compared against the checked-in `dune.inc`
   files. `--auto-promote` copies the generated versions into the source tree
   so dune picks up the new test targets.
4. Run the tests a second time (now that `dune.inc` is up to date, the new
   images will be generated and promoted into `actual/`):
   ```bash
   opam exec -- dune build @runtest
   ```
5. Inspect the generated `.png` in `actual/`, then copy it to `expected/`.
