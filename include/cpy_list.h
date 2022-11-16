#ifndef CPY_LIST_H
#define CPY_LIST_H

#include "cpy_core.h"

void __list_add(int argc, unsigned short argv[], ...);
int __list_index(int argc, unsigned short argv[], ...);
void list_free(cpy_list* list);
int list_len(cpy_list* list);

/**
 * Pass any number of strings
 * and numbers as argument.
 */
#define list_add(a...) ({ va_argv(__list_add, a); })

/**
 * Get index of an item in a list.
 *
 * @param {List} list
 * @param {Str_t | Num_t} item
 * @param optional {int} start
 * @param optional {int} end
 *
 * @returns {int} Index of item.
 * Returns -1 if not found.
 */
#define list_index(a...) ({ va_argv(__list_index, a); })  // NOLINT

#endif  // CPY_LIST_H
