### CMake Presets

This project makes use of [CMake Presets][1] to simplify the process of configuring
the project.

To build the project, please make sure you have [vcpkg][2]
installed and properly set up at least with the `VCPKG_ROOT` environment variable pointing
to the right place.

### List Presets
```
cmake --list-presets=all .
```

### Configure & Build
```
cmake --preset=x64-debug
```
```
cmake --build --preset=x64-debug
```

[1]: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
[2]: https://github.com/microsoft/vcpkg

