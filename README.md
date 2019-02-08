Create the project with Visual Studio and CMake:
```
cmake -G "Visual Studio 14 2015" -A x64 -DCMAKE_INSTALL_PREFIX=<install directory>
cmake --build . –-parallel 4 --config Release
cmake --build . --target lib/install 
```