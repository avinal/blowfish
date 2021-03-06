# Blowfish Encryption Algorithm 

<p align=center><a href="https://github.com/avinal/blowfish/actions"><img alt="build" src="https://github.com/avinal/blowfish/workflows/build/badge.svg?branch=main"></a><a href="https://github.com/avinal/blowfish/blob/main/LICENSE"><img src="https://img.shields.io/github/license/avinal/blowfish" alt="license"></a></p>


Blowfish is a symmetric block cipher that can be used as a drop-in replacement for DES or IDEA. It takes a variable-length key, from 32 bits to 448 bits, making it ideal for both domestic and exportable use. Blowfish was designed in 1993 by Bruce Schneier as a fast, free alternative to existing encryption algorithms. Since then it has been analyzed considerably, and it is slowly gaining acceptance as a strong encryption algorithm. Blowfish is unpatented and license-free, and is available free for all uses.

## About this project

This is a C++ implementation of the encryption algorithm.

## How to use this in your project?
1. You may fork it and use it like any other source file in your project. You only need [blowfish.hpp](include/blowfish/blowfish.hpp) and [blowfish.cpp](src/blowfish.cpp) files. Just modify the header as per your convienence. 
2. If you are using CMake, the work is lot easier. You can add this as a git submodule. It isolates your project from this dependency. 
  ```bash
    # In your project root type these commands
    git submodule add https://github.com/avinal/blowfish
    # considering this addition is your only change
    git commit -m "blowfish submodule added"
    git push origin main
 ```
 Add this to your CMakeLists.txt as well.
    

## References
- [Description of a new variable-length key, 64-bit block cipher (Blowfish)](https://link.springer.com/chapter/10.1007/3-540-58108-1_24)
- [The Blowfish Encryption Algorithm](https://www.schneier.com/academic/blowfish/)
