#ifndef CPY_CORE_H
#define CPY_CORE_H

#include <stdbool.h>

#include "cpy_types.h"

typedef struct {
  int* type;
  char** string;
  int stringc;
  double* num;
  int numc;
} cpy_list;

// Data type initializers.

#define create_list_t()                   \
  ({                                      \
    cpy_list l;                           \
    l.string = malloc(sizeof(char*) * 1); \
    l.stringc = 0;                        \
    l.num = malloc(sizeof(double) * 1);   \
    l.numc = 0;                           \
    l.type = malloc(sizeof(int) * 1);     \
    &l;                                   \
  })

// clang-format off
#define new(TYPE) create_##TYPE();
// clang-format on

#define type(a)                               \
  ({                                          \
    unsigned short stack[1], *_p = stack + 1; \
    (void)__print_types(a);                   \
    _p[0] & 0x1F;                             \
  })

#define va_argc(a...) __print_count(a)  // nothing: sizeof()

#define va_argv(function, a...)                       \
  ({                                                  \
    int count = va_argc(a);                           \
    unsigned short stack[count], *_p = stack + count; \
    __print_types(a);                                 \
    function(count, _p, a);                           \
  })
#define va_type(variable) (variable & 0x1F)

#endif  // CPY_CORE_H
