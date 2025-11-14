# SMEStencil_Baselines

## Repo Structure

- sve_brick_1642/:  corresponding to "highly optimized SIMD version" baselines, in single precision and brick layout of (16, 4, 2)
- sme_brick_1644/:  our optimized stencil kernels based on SME instrunction set, in single precision and brick layout of (16, 4, 4)
- test_scripts/:  containing "compiler optimized stencil" baselines and scripts to generate benchmarks from kernel
- RTM/: containing our optimized SIMD version and SME accelerated RTM TTI kernel implementations

## Test Environment

The platform information is not yet revealed

Compiler: Bisheng 5.0.0

compile command for naive and simd version:

```bash
clang++ -O3 -march=armv8.4-a+sve -ffast-math -mcpu=hip11 -fomit-frame-pointer -fopenmp -stdlib=libc++ -rtlib=compiler-rt <your benchmark.cpp> -o <your executable>
```

compile command for sme version:

```bash
clang++ -O3 -march=armv8.4-a+sve+sme -ffast-math -mcpu=hip11 -fomit-frame-pointer -fopenmp -Wno-undefined-arm-za -stdlib=libc++ -rtlib=compiler-rt <your benchmark.cpp> -o <your executable>
```

run your program:

```bash
OMP_NUM_THREADS=38 OMP_PROC_BIND=close numactl --membind=16 --cpubind=0 ./<program> <domain size>
```

## How to Generate Benchmarks 

first enter test_script/ directory, then use python to run templateGen.py

```bash 
python3 templateGen.py
		--input_layout brick
		--output_layout brick
		--function <your kernel>
		--radius <stencil radius of kernel>
		--tile_size <your tile size>
		--brick_size <brick layout>
		--affine # add this in 3D kernels of SME
		--align
		--nflops <stencil FLOPS>
```

