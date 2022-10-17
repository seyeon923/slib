#ifndef SLIB_INCLUDE_SLIB_UTILS_H_
#define SLIB_INCLUDE_SLIB_UTILS_H_

#include <stddef.h>

#define SLIB_CONTAINER_OF(ptr, type, member) \
    ((type*)((char*)ptr - offsetof(type, member)))

#endif  // SLIB_INCLUDE_SLIB_UTILS_H_