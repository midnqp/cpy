/************************************************
 * cpyb.h
 * Python builtins implemented in C
 * Source: github.com/midnqp/cpyb
 *
 * Copyright (C) 2021 Muhammad <midnqp@gmail.com>
 * Licensed under MIT License
 ************************************************/

#ifndef CPY_H
#define CPY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdbool.h>
#include <cpy-print.h>
#include <float.h>

#ifdef _WIN32
    #include <Windows.h>
    #include <io.h>
#else
    #include <unistd.h>
    #include <dirent.h>
#endif


/* stdarg   :: va_list ...
 * stdio    :: printf FILE perror ...
 * stdlib   :: malloc realloc exit ...
 * string   :: strcat strcpy ...
 * sys/stat :: mkdir ...
 * ctype    :: isalpha ...
 * float    :: FLT_MAX ...
 *
 * unistd   :: sleep
 * dirent   :: dir_exists
 *
 * Windows  :: Win32 everything ...
 * io       :: _read
 */


#define new(_type, _bytes) (_type)malloc(_bytes + 1)


enum types {
    t_double,
    t_char,
    t_int,
    t_str,
    t_long,
    t_float,
    t_numlist,
	t_intlist,
	t_unknown
	// You can add more.
};


// Needs explicit type cast.
void* var(int t_type, int n_items); 


#define type(variable) _Generic(variable, \
    int    : t_int,    \
    char   : t_char,   \
    char*  : t_str,    \
    long   : t_long,   \
    double : t_double, \
    float  : t_float,  \
    default: t_unknown)
//More stuffs could be added. For now these.


char* file_read(const char* filename);
long file_size(const char* filename);
void file_write(const char* filename, const char* buffer);
void file_append(const char* filename, const char* buffer);
int file_exists(const char* fn);
int file_remove(const char* fn);

int dir_exists(const char* dirName);
char* input(const char* prompt);


/* Only works if in the same scope.
 * double arr[] = {1, 2};
 * print(list_len(arr));
 */
#define list_len(arr) (sizeof(arr)/sizeof(*arr))
double list_max(double numbers[], int arrlen);
double list_min(double numbers[], int arrlen);
double list_sum(double numbers[], int arrlen);


char* __str_add_va__(const char* strings, ...);
#define str_add(...) __str_add_va__(__VA_ARGS__, NULL)
#define str_len(pointer) strlen(pointer)
int str_count(const char* string, const char* substr, int start, int end);
int str_eq(const char* a, const char* b);
int str_index(const char* str, const char* substr, int start, int end);
int str_isalpha(const char* string);
char* str_put(char* variable, char* value);
void strPut(char* variable, char* value); 
#define strAdd(variable, ...) {\
	char* __strAddInternal = str_add(variable, __VA_ARGS__);\
	strPut(variable, __strAddInternal);\
}
char* str_replace(const char* main, const char* repl, const char* with, int start, int end);
char* str_reverse(const char* string);
char* str_slice(const char* string, int start, int step, int end);
char** str_split(const char* a_str, const char* a_delim);
char* str_substr(const char* string, const char* substr);


#define TBSP "    "
#define ESC "\033["
#define R00 ESC "0;0m" //resets all attributes
#define R0 ESC "0m"    // resets color attributes
#define BLK(string, ...) COLOR("30m", string)
#define RED(string, ...) COLOR("31m", string)
#define GRN(string, ...) COLOR("32m",string)
#define YLW(string, ...) COLOR("33m",string)
#define BLU(string, ...) COLOR("34m",string)
#define MGN(string, ...) COLOR("35m",string)
#define CYN(string, ...) COLOR("36m",string)
#define GRY(string, ...) COLOR("37m",string)


#define BLKBG(string, ...) COLOR("40m", string)
#define REDBG(string, ...) COLOR("41m", string)
#define GRNBG(string, ...) COLOR("42m", string)
#define YLWBG(string, ...) COLOR("43m", string)
#define BLUBG(string, ...) COLOR("44m", string)
#define MGNBG(string, ...) COLOR("45m", string)
#define CYNBG(string, ...) COLOR("46m", string)
#define GRYBG(string, ...) COLOR("47m", string)
#endif ////// CPY_H

