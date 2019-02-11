# Introduction

This is an example project on how to build a library using CMake. The library itself is programmed in C++. The problem with C++ is that the functions are [name mangled](https://en.wikipedia.org/wiki/Name_mangling) which is not standardized. This can result in that different compilers could produce different mangled names. In short name mangling means that the compiler will extend the function name so that it is distinct even for overloaded functions. Suppose you have two functions in your library:

```
doSomething()
doSomething(int)
```

This would not be allowed in C but it is allowed in C++. The actual names of the functions after compiling could be:

```
_Z11doSomethingi
_Z11doSomethingv
```

If you want to use a shared C++ library you should use the same compiler for compiling the library and the program because of this.

This is example library is written such that it should be possible to compile on Linux and Windows. Developing libraries on Windows is a little bit different to developing libraries on Linux in that for Windows it is necessary to export the library functions explicitly. There are two possibilities to export symbol names on Windows:

* Writing a def file which lists all functions which should be made visible in the DLL
* Mark the functions which should be exported with `__declspec(dllexport)`

There is a comparison provided by Microsoft which compares the two different methods: [Determining Which Exporting Method to Use](https://docs.microsoft.com/en-us/cpp/build/determining-which-exporting-method-to-use?view=vs-2017). It gets even more complicated when the library is build on x86 because the compiler needs to know the calling convention of the function [x86 calling conventions](https://en.wikipedia.org/wiki/X86_calling_conventions). Luckily the calling convention is standardized for x86-64.

When a def file is used the header file does not have to be modified. In case the symbols were exported with `__declspec(dllexport)` the header file which is used by the program which uses the library should mark these functions with `__declspec(dllimport)`. This is optional though ([Importing into an Application Using __declspec(dllimport)](https://docs.microsoft.com/en-us/cpp/build/importing-into-an-application-using-declspec-dllimport?view=vs-2017)).

It could be useful to not export all symbols on Linux also to prevent that internal functions are misused. This is done by setting the target properties `CXX_VISIBILITY_PRESET` and `VISIBILITY_INLINES_HIDDEN` for the `cppLibrary` library.

To alleviate the name mangling problem with C++ libraries a typical approach is to create a wrapper for the library which exports C functions which is done in this case.

The project also includes an executable target which links to target as an example on how to include the library in another project.


# Create the Project With Visual Studio and CMake

The following command will configure, build and then install the library.
```
cmake -G "Visual Studio 14 2015" -A x64 -DCMAKE_INSTALL_PREFIX=<install directory> <path to project root>
cmake --build . –-parallel 4 --config Release
cmake --build . –-parallel 4 --config Release --target lib/install 
```

The library can be build as static library when cmake is configured with `-DBUILD_SHARED_LIBS=OFF`.

If the executable should be build `DBUILD_EXECUTABLE=ON` has to be passed to CMake.

# Remarks
When building the library as shared library the functions can be viewed with [DLL Export Viewer](http://www.nirsoft.net/utils/dll_export_viewer.html). The library should only contain `closeLibrary`, `createLibrary`, `wrapFunction1` and `wrapFunction2` function names.

You can try to build the library again with:

```
$ cmake -G "Visual Studio 14 2015" -A x64 -DCMAKE_INSTALL_PREFIX=<install directory> -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=ON <path to project root>
$ cmake --build . –-parallel 4 --config Release
```

Now if you open the DLL you should see a lot more function names because CMake will create a .def file where all functions names will be exported to ([
Create dlls on Windows without declspec() using new CMake export all feature](https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/)).