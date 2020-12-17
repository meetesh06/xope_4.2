# xope_4.2
 XOPE Programming Language

Supported OS: Ubuntu 64 bit or equivalent linux distro
Supported Asesmbler: NASM 
Recommended Intel Processor

Check out examples folder to see how this works,
https://github.com/meetesh06/xope_4.2/tree/main/examples

xope_installer.sh can be used to install the dependencies and 
add xope command to path

Some interesting quirks about XOPE,
It uses some custom implementation for printing stuff to screen instead of printf
It has been heavily optimized assembly code for things xope can do, check out base/headers.c
like printing multi digit numbers, etc.

The code is heavily commented and should be easy to read and compile
make sure to use a stable make release to compile the code.
