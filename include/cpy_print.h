/**
 * File: Generic Print
 *
 * Copyright 2021 Exebook
 * MIT License
 */
#ifndef CPY_PRINT_H
#define CPY_PRINT_H

#include <stdio.h>

#include "cpy_types.h"

extern int __print_enable_color;
void __print_color(FILE *fd, int a);

#define __print_array(fd, T, qual, color)                 \
  __print_color(fd, __print_color_normal);                \
  int max_len = 16;                                       \
  int n = size / sizeof(T);                               \
  T *m = va_arg(v, T *);                                  \
  fprintf(fd, "[");                                       \
  __print_color(fd, color);                               \
  for (int i = 0; i < (n < max_len ? n : max_len); i++) { \
    if (i > 0) fprintf(fd, " ");                          \
    fprintf(fd, qual, m[i]);                              \
  }                                                       \
  __print_color(fd, __print_color_normal);                \
  if (n > max_len) fprintf(fd, "...");                    \
  fprintf(fd, "]");

extern int __print_color_normal;  // -1 means default terminal foreground color
extern int __print_color_number;
extern int __print_color_string;
extern int __print_color_hex;
extern int __print_color_float;

void __print_setup_colors(int normal, int number, int string, int hex,
                          int fractional);
DllExport void __print_func(FILE *fd, int count, unsigned short types[], ...);

// clang-format off
#define __print_typeid(a) \
	__builtin_choose_expr(__print_is_type(a, cpy_list*), cpy_list_t, \
	__builtin_choose_expr(__print_is_type(a, bool), cpy_bool_t, \
	__builtin_choose_expr(__print_is_type(a, double), cpy_double_t, \
	__builtin_choose_expr(__print_is_type(a, double*), cpy_listd_t, \
	__builtin_choose_expr(__print_is_type(a, float), cpy_float_t, \
	__builtin_choose_expr(__print_is_type(a, char), cpy_char_t, \
	__builtin_choose_expr(__print_is_type(a, unsigned char), cpy_uchar_t, \
	__builtin_choose_expr(__print_is_type(a, int), cpy_int_t, \
	__builtin_choose_expr(__print_is_type(a, unsigned int), cpy_uint_t, \
	__builtin_choose_expr(__print_is_type(a, long), cpy_long_t, \
	__builtin_choose_expr(__print_is_type(a, unsigned long), cpy_ulong_t, \
	__builtin_choose_expr(__print_is_type(a, short), cpy_short_t, \
	__builtin_choose_expr(__print_is_type(a, char*), cpy_str_t, \
	__builtin_choose_expr(__print_is_type(a, char[]), cpy_arrc_t, \
	__builtin_choose_expr(__print_is_type(a, void*), cpy_void_t, \
	__builtin_choose_expr(__print_is_type(a, double[]), cpy_arrd_t, \
	__builtin_choose_expr(__print_is_type(a, unsigned int[]), cpy_arru_t, \
	__builtin_choose_expr(__print_is_type(a, short[]), cpy_arrhi_t, \
	__builtin_choose_expr(__print_is_type(a, unsigned short[]), cpy_arrhu_t, \
	__builtin_choose_expr(__print_is_type(a, char*[]), cpy_arrs_t, \
	__builtin_choose_expr(sizeof(a) == 1, 2, \
	__builtin_choose_expr(sizeof(a) == 2, 4, \
	0  ))))))))))))))))))))))

#define __print_push(c,size,cont) (cont, *--_p = c | (size << 5))
#define __builtin_choose_expr __builtin_choose_expr
#ifdef _WIN32
#define __print_is_type(a, t) __builtin_types_compatible_p(typeof(a), t)
#else
#define __print_is_type(a, t) __builtin_types_compatible_p(typeof(a), t)
#endif
#define __print_count_int(q,w,e,r,t,y,u,i,o,p,a,s,d,f,g,h,j,k,l,z,x,c,v,b,n,m,...) m

#ifdef _WIN32
#define __print_count(...)__print_count_int(__VA_ARGS__,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#else
#define __print_count(a...) __print_count_int(a,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
#endif

#define __print_code(a, cont) __builtin_choose_expr(__print_is_type(a, void), 0, __print_push(__print_typeid(a), (sizeof(a)<(1<<16>>5) ? sizeof(a):(1<<16>>5)-1), cont))

#define __print_types_int(q,w,e,r,t,y,u,i,o,p,a,s,d,f,g,h,j,k,l,z,x,c,v,b,n,m,...) __print_code(q,__print_code(w,__print_code(e,__print_code(r,__print_code(t,__print_code(y,__print_code(u,__print_code(i,__print_code(o,__print_code(p,__print_code(a,__print_code(s,__print_code(d,__print_code(f,__print_code(g,__print_code(h,__print_code(j,__print_code(k,__print_code(l,__print_code(z,__print_code(x,__print_code(c,__print_code(v,__print_code(b,__print_code(n,__print_code(m, 0))))))))))))))))))))))))))

#ifdef _WIN32
#define __print_types(...) __print_types_int(__VA_ARGS__, 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)
#else
#define __print_types(a...) __print_types_int(a, (void)0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1) 
#endif

// clang-format on
// If you remove the ({}), then reclaration error appears!
#ifdef _WIN32
#define fprint(fd, ...)                             \
  ({                                                \
    int count = __print_count(__VA_ARGS__);         \
    unsigned short *stack = malloc(count);          \
    unsigned short *_p = stack + count;             \
    (void)__print_types(__VA_ARGS__);               \
    (void)__print_func(fd, count, _p, __VA_ARGS__); \
  })

#else
#define fprint(fd, a...)                              \
  ({                                                  \
    int count = __print_count(a);                     \
    unsigned short stack[count], *_p = stack + count; \
    (void)__print_types(a);                           \
    (void)__print_func(fd, count, _p, a);             \
  })
#endif

#ifdef _WIN32
#define print(...) (void)fprint(stdout, __VA_ARGS__);
#else
#define print(a...) (void)fprint(stdout, a);
#endif

#endif  // CPY_PRINT_H
