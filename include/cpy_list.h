#ifndef CPY_LIST_H
#define CPY_LIST_H

#include "cpy_core.h"
#include "cpy_types.h"

DllExport cpy_list* cpy_new_cpy_list_t();
void __list_add(int argc, unsigned short argv[], ...);
int __list_index(int argc, unsigned short argv[], ...);
DllExport void list_free(cpy_list* list);
int list_len(cpy_list* list);

/**
 * Pass any number of strings
 * and numbers as argument.
 */
#ifdef _WIN32
#define list_add(...) ({ va_argv(__list_add, __VA_ARGS__); })
#else
#define list_add(a...) ({ va_argv(__list_add, a); })
#endif

/**
 * Get index of an item in a list.
 *
 * @param {cpy_list_t} list
 * @param {cpy_num_t | cpy_str_t} item
 * @param optional {int} start
 * @param optional {int} end
 *
 * @returns {int} index of item.
 * Returns -1 if not found.
 */
#ifdef _WIN32
#define list_index(...) ({ va_argv(__list_index, __VA_ARGS__); })
#else
#define list_index(a...) ({ va_argv(__list_index, a); })
#endif

#endif  // CPY_LIST_H
