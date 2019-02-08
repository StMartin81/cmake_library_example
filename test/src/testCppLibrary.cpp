#include "cppLibrary/library_wrapper.h"
#include <iostream>

int main()
{
    std::cout << "Create new library instance" << std::endl;
    size_t handle{createLibrary()};
    wrapFunction1(handle);
    wrapFunction2(handle);
    closeLibrary(handle);
    std::cout << "Library instance deleted" << std::endl;
    return 0;
}
