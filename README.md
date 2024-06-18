# expression-compiler

## How to compile
First clone the repository

```bash
git clone https://github.com/OmarAzizi/expression-compiler.git && cd expression-compiler
```

Then make the `build` directory and change into it

```bash
mkdir build && cd build
```

Run the build command 

```bash
cmake -GNinja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_DIR=/usr/lib/llvm ../ && ninja
```

Then go into the `src` directory inside of `build` where you will find the `calc` executable and run the following command:


```bash
./calc "with a: a*3" | llc -filetype=obj -relocation-model=pic -o=expr.o
```
The expression could be changed to anything you want, with any amount of variables

Then link `exrpr.o` with the runtime library `rtcalc.c` as follows:
```bash
clang -o expr expr.o ../../rtcalc.c
```
