#ifndef CPY_LIST_H
#include "cpy_core.h"
#define CPY_LIST_H

void list_add(int argc, unsigned short argv[], ...);
int list_index(int argc, unsigned short argv[], ...);
void listFree(List* list);
int listLen(List* list);

/**
 * Pass any number of strings
 * and numbers as argument.
 */
#define listAdd(a...) ({ va_argv(list_add, a); })

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
#define listIndex(a...) ({ va_argv(list_index, a); })

#endif
