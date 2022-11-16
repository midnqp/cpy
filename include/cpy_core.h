#include <stdbool.h>
#ifndef CPY_CORE_H
#define CPY_CORE_H

// Data type definition.

enum TYPE {
  Void_t = 10,
  Float_t = 1,
  Int_t = 4,
  Short_t = 4,
  Char_t = 2,
  Str_t = 8,
  Uchar_t = 3,
  Uint_t = 5,
  Long_t = 6,
  Ulong_t = 7,
  Double_t = 1,
  Num_t = 1,
  Bool_t = 17,
  List_t = 18,
  DoubleList_t = 19,
  FloatList_t = 20,
  // Literals...
  StrArray_t = 15,
  CharArray_t = 9,
  UintArray_t = 12,
  ShortArray_t = 13,
  UshortArray_t = 14,
  DoubleArray_t = 11,
  FloatArray_t = 21,

  Unknown_t = 0,
};

typedef struct {
  int* type;
  char** string;
  int stringc;
  double* num;
  int numc;
} List;

// Data type initializers.

#define create_List_t()                      \
  ({                                         \
    List list;                               \
    list.string = malloc(sizeof(char*) * 1); \
    list.stringc = 0;                        \
    list.num = malloc(sizeof(double) * 1);   \
    list.numc = 0;                           \
    list.type = malloc(sizeof(int) * 1);     \
    &list;                                   \
  })

// Helper utilities.

void cpyErr(const char* e_msg, bool crash);

// clang-format off
#define new(TYPE) create_##TYPE();
// clang-format on

#define type(a)                               \
  ({                                          \
    unsigned short stack[1], *_p = stack + 1; \
    (void)__print_types(a);                   \
    _p[0] & 0x1F;                             \
  })

#define va_argc(a...) __print_count(a)

#define va_argv(function, a...)                       \
  ({                                                  \
    int count = va_argc(a);                           \
    unsigned short stack[count], *_p = stack + count; \
    __print_types(a);                                 \
    function(count, _p, a);                           \
  })
#define va_type(variable) (variable & 0x1F)

#endif
