# expression-compiler
This is just me practicing compiler engineering after a long time of not doing so :)

## How to Compile
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
**Note**: The expression could be changed to anything you want, with any amount of variables

Then link `expr.o` with the runtime library `rtcalc.c` as follows:
```bashclang -o expr expr.o ../../rtcalc.c
clang -o expr expr.o ../../rtcalc.c
```
After running the `expr` executable you will be asked to input a value for `a`

## Example of compiling an expression
![image](https://github.com/OmarAzizi/expression-compiler/assets/110500643/2c14dfef-b7a3-41c9-bf79-857124d7b089)

