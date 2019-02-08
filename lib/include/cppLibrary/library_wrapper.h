#ifndef LIBRARY_WRAPPER_H
#define LIBRARY_WRAPPER_H

#include "cppLibrary/cppLibrary_export.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

CPPLIBRARY_EXPORT size_t createLibrary();
CPPLIBRARY_EXPORT size_t closeLibrary(size_t const handle);
CPPLIBRARY_EXPORT void wrapFunction1(size_t const handle);
CPPLIBRARY_EXPORT void wrapFunction2(size_t const handle);

#ifdef __cplusplus
}
#endif

#endif // LIBRARY_WRAPPER_H
