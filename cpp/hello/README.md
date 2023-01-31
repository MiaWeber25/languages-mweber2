# Hello in C++

This project is a tested hello function that can return greeting messages.

This is a template for your C/C++ projects. Adapt this to your own projects to turn in assignments.

## Overview

All the commands below assume you are running in a unix-like shell, which is a regular terminal on OS X/Linux, or any of Git-bash, MSys2, or WSL in Windows.  If `ls` (directory listing) works then you are probably ok.

1. The hello function prototype is in `include/hello.h`. You should put all
   your header (.h) files in the `include` directory.
1. The hello function definition is in `src/hello.cpp`.  You should put all
   your source files (.cpp for C++ and .c for C) in the `src` directory.
1. The hello unit tests are in `src/test_hello.cpp`.  You should put all your
   unit tests in `src/test_<things_to_test>.cpp`.  After building (`make all`), you can run these tests with `./bin/test_<things_to_test>` or `./test_all` to test all the things.
2. The hello main executable is in `src/main_hello` and `make all` builds `./bin/hello`.  You can have multiple executables, just name the corresponding source file with a `main` function in `src/main_<program>.cpp` or `src/main_<program>.c`.  Running `make all` will build `./bin/<program>`.
3. With docker installed, you can run all of these in a container with `./run <command>`.  For example 
```sh
./run ./test_all
```
will make everything and run the tests in the docker container defined in `Dockerfile`.

## Details

Structure your project as:
```
include/*.h -- C or C++ header files
src/*.cpp -- C++ source files
src/*.c   -- C source files
src/test_<thing>.cpp -- googletest unit tests for <thing> (bin/test_<thing>)
src/main_<program> -- main program (bin/<program>)
```
The Makefile will build the corresponding tests and programs with `make all`
You can make everythinig and run all the tests with `./test_all`.

If you are using docker, then the run script will build the docker and run the corresponding command.


Here, `<arch>` is "$(uname -s)-$(uname -m)" like `Darwin-x86_64`.  This way the
same folder can support multiple architectures.

You can use make clean/all without modifying Makefile and Makefile.googletest

## Build

```bash
make clean
make all
```

## Test

```bash
./test_all
```

## Run

The "uname" business makes things work even if you have muliple architectures (like with docker below).

```bash
./bin/hello
```
## Clean-Build-Test Screen Capture

![clean-test-build.png](clean-build-test.png)

## Docker

To create a reproducible build (advanced) and you have docker installed, you can do the following (use a git-bash shell in windows, WSL may work):

```bash
./run test_all # test
./run hello # run
./run # give me a shell in the docker container
```
## References

1. [GNU make tutorial](https://linuxhint.com/gnu-make-tutorial/)
1. [C++ Google Test](https://github.com/google/googletest)
1. [Google Test Primer](https://www.learncpp.com/cpp-tutorial/89-class-code-and-header-files/)
1. [src/include](https://www.learncpp.com/cpp-tutorial/89-class-code-and-header-files/)


