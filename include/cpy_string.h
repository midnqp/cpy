#ifndef CPY_STRING_H
#define CPY_STRING_H

#include "cpy_core.h"

char* str_add_va(const char* strings, ...);
char* str_put(char* variable, char* value);
void strPut(char* variable, char* value);

/**
 * Checks if @string is alphanumeric.
 * @returns {bool}
 */
bool strAlnum(const char* string);

/**
 * Counts the occurrences of @substr in @str.
 *
 * @param {const char*} str
 * @param {const char*} substr
 * @param {int} start Optional
 * @param {int} end Optional
 *
 * @returns {int}
 */
int strCount(const char* str, const char* substr, int start, int end);

/**
 * Checks if the strings @foo and @bar are equal.
 *
 * @param {const char*} foo
 * @param {const char*} bar
 * @param {bool} caseSensitive. Optional. Default: true.
 *
 * @returns {bool}
 */
bool strEq(const char* foo, const char* bar);

int strIndex(const char* str, const char* substr, int start, int end);
void strReplace(const char* str, const char* a, const char* b);
void strReverse(char* dest, const char* string);
void strSlice(char* dest, const char* str, int start, int end);
void strSplit(cpy_list* dest, const char* a_str, const char* a_delim);
void strSub(char* dest, const char* string, const char* substr);

#define _str_add(...) str_add_va(__VA_ARGS__, NULL)
#define strAdd(var, ...)                    \
  ({                                        \
    char* tmp = _str_add(var, __VA_ARGS__); \
    strPut(var, tmp);                       \
  })
#define strLen(pointer) strlen(pointer)

#endif
