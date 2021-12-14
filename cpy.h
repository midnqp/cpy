#ifndef CPY_H
#define CPY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdbool.h>
#include "cpy-print.h"
#include "cpy-colors.h"
#include <float.h>
#ifdef _WIN32
    #include <Windows.h>
    #include <io.h>
#else
    #include <unistd.h>
    #include <dirent.h>
#endif


//////////////////////////
// CPY CORE INITIATIONS //
//////////////////////////

enum types {
    t_double,
    t_char,
    t_int,
    t_str,
    t_long,
    t_float,
    t_num_list,
	t_int_list,
	t_unknown
	// You can add more.
};
#define vargc(args...) __print_count(args) //count 
#define new(_type, _bytes) (_type)malloc(_bytes + 1)
#define typeOf(a) ({\
	unsigned short stack[1], *_p = stack + 1;\
	__print_types(a);\
	_p[0] & 0x1F; \
})
#define type(variable) _Generic(variable, \
    int    : t_int,    \
    char   : t_char,   \
    char*  : t_str,    \
    long   : t_long,   \
    double : t_double, \
    float  : t_float,  \
    default: t_unknown)
	// You can add more.
#define var(variable, t_type, n_items) \
	if (t_type == t_num_list) {\
		size_t _a_ = sizeof(double) * n_items;\
		variable.value = (double*)malloc(_a_);\
		variable.len = n_items;\
		for (int i=0; i < n_items; i++) {\
			variable.value[i] = DBL_MAX;\
		}\
	}


////////////////////////
// CPY FILE FUNCTIONS //
////////////////////////

char* file_read(const char* filename);
void file_write(const char* filename, const char* buffer);
void file_remove(const char* fn);
void file_append(const char* filename, const char* buffer);
long file_size(const char* filename);
bool file_exists(const char* fn);
bool dir_exists(const char* dirName);
char* input(const char* prompt);


////////////////////////
// CPY LIST FUNCTIONS //
////////////////////////

// TODO Make list support all data types.
typedef struct __list__ {
	double* value;
	int len;
} List;
double list_get(List list, int index);
void list_set(List list, int index, double item);
bool list_includes(List list, double item);
void list_push(List list, double item);
#define list_append(...) list_push(__VA_ARGS__)
void list_remove(List list, int index);
int list_len(List list);
int list_index(List list, double item, int start, int end);
double list_max(List list);
double list_min(List list);
double list_sum(List list);
List list_dup(List list);
List list_sort(List list);


//////////////////////////
// CPY STRING FUNCTIONS //
//////////////////////////

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

#endif // CPY_H

