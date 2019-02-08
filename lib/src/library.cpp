#include "library.h"
#include <iostream>

Library::Library()
{
    std::cout << "Library constructor" << std::endl;
}

Library::~Library()
{
    std::cout << "Library destructor" << std::endl;
}

void Library::function1()
{
    std::cout << "function1" << std::endl;
}

void Library::function2()
{
    std::cout << "function2" << std::endl;
}
