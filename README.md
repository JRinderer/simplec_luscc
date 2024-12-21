# LUSCC Lewis University Simple C Compiler
This is an educational compiler written in C that is designed to compile a very simple subset of C. It reads C code and generates x86_64 assembly code that can be assembled and linked into an executable. The compiler is written in C and is designed to be simple and easy to understand. It is not designed to be fast or to generate efficient code. It is designed to be a learning tool for people who want to learn how compilers work.

## Examples of LUSCC 
all luscc files will have an luscc extension
```
```main.luscc
```
### Example code
```c
int main() {
    int x = 5;
    int y = 10;
    int z = x + y;
    printf("The sum of %d and %d is %d\n", x, y, z);
}
```

