# qtwebcall


# Developing and running a Qt application with VSCode

## Prerequisites

- Qt installed
- Cmake installed
- CMakeLists.txt file
- CMakePresets.json file
- .vscode/c_cpp_properties.json file
- .vscode/launch.json file
- .vscode/settings.json file
. .vscode/tasks.json file



## Cmake

- Setup

```bash
cmake --preset Desktop-Debug -B build/Desktop-Debug -S .
```

```
#maybe
cmake -DCMAKE_PREFIX_PATH=/home/sr/Qt/6.8.1/gcc_64 -S . -B build/Desktop-Debug
``` 

- Building

```bash
cmake --build build/Desktop-Debug --target clean
cmake --build build/Desktop-Debug --target all
```

