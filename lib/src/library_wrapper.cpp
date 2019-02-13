#include "cppLibrary/library_wrapper.h"
#include "library.h"
#include <unordered_map>
#include <functional>
#include <memory>

static std::unordered_map<size_t, std::unique_ptr<Library>> instances;

size_t createLibrary()
{
    std::unique_ptr<Library> libraryPtr{std::make_unique < Library >() };
    size_t handle{std::hash<std::unique_ptr<Library>>()(libraryPtr)};
    instances.insert(std::make_pair(handle, std::move(libraryPtr)));
    return handle;
}

size_t closeLibrary(size_t const handle)
{
    return instances.erase(handle);
}

void wrapFunction1(size_t const handle)
{
    instances[handle]->function1();
}

void wrapFunction2(size_t const handle)
{
    instances[handle]->function1();
}
