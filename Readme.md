# List Presets

- ```cmake --list-presets=all .```

# Configure & Build

- ```cmake --preset=x64-debug```
- ```cmake --build --preset=x64-debug```

# Build Environment
- Add the folders with the executable files of the following programs to the system paths.

1. [LLVM](https://releases.llvm.org/)
2. [CMake](https://cmake.org/)
3. [Ninja](https://github.com/ninja-build/ninja)
4. [vcpkg](https://vcpkg.io/en/) (set VCPKG_ROOT env variable)