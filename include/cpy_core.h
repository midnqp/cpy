#ifndef CPY_CORE_H
#define CPY_CORE_H

#ifdef _WIN32
#define DllExport __declspec(dllexport)
#else
#define DllExport
#endif

#include <stdbool.h>
#include <stdio.h>

#include "cpy_types.h"
// clang-format off

typedef struct
{
  int *type;
  char **string;
  int stringc;
  double *num;
  int numc;
} cpy_list;

#define cpy_new(TYPE) cpy_new_##TYPE()

#define cpy_type(a)                           \
  ({                                          \
    unsigned short stack[1], *_p = stack + 1; \
    (void)__print_types(a);                   \
    _p[0] & 0x1F;                             \
  })

#ifdef _WIN32
#define va_argc(...) __print_count(__VA_ARGS__)
#else
#define va_argc(a...) __print_count(a)
#endif

#ifdef _WIN32
#define va_argv(function, ...) {                   \
  int count = va_argc(__VA_ARGS__);                 \
  unsigned short *stack = malloc(count);\
  unsigned short *_p = stack + count; \
  __print_types(__VA_ARGS__);                       \
  function(count, _p, __VA_ARGS__);                 \
  free(stack);\
}
#else
#define va_argv(function, a...)                           \
({                                                       \
        int count = va_argc(a);                           \
        unsigned short stack[count], *_p = stack + count; \
        __print_types(a);                                 \
        function(count, _p, a);                           \
})
#endif

#define va_type(variable) ((variable & 0x1F))

#endif // CPY_CORE_H
// clang-format on