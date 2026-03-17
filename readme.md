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
├── main.c               — CPU backend demo
├── lux_cpu.c            — CPU backend implementation
├── lux_cpu.h
└── dune
gpu/
├── main.c               — GPU backend demo
├── kernel.cu            — GPU kernel (compiled at runtime via NVRTC)
└── dune
```

## Design Decisions

**Runtime compilation with NVRTC instead of nvcc.**  The host code is compiled
with plain `gcc`. The CUDA kernel source is kept in a separate `kernel.cu` file
which gets loaded as a string and compiled at runtime via NVRTC. This means the
edit-run cycle for kernel code doesn't require a recompile of the host program.

**CUDA Driver API instead of Runtime API.**  Since we're using NVRTC to compile
kernels at runtime, we use the CUDA Driver API (`cuMemAlloc`, `cuLaunchKernel`,
etc.) rather than the Runtime API (`cudaMalloc`, `<<<>>>` syntax). The Driver API
gives explicit control over contexts, modules, and kernel launches, which pairs
naturally with runtime-compiled PTX.

**dune as the build system.**  Each subdirectory has a `dune` file with custom
rules that invoke `gcc` directly. This keeps the build declarative and incremental
without needing CMake or Makefiles.

## Usage

```bash
# build and run the CPU backend
dune build @cpu/run

# build and run the GPU backend
dune build @gpu/run

# build a specific target
dune build cpu/main.exe
dune build gpu/main.exe
```
