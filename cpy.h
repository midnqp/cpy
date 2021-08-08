/************************************************
 * cpyb.h
 * Python builtins implemented in C
 * Source: github.com/midnqp/cpyb
 *
 * Copyright (C) 2021 Muhammad <midnqp@gmail.com>
 * Licensed under MIT License
 ************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

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
 *
 * unistd   :: sleep
 * dirent   :: dir_exists
 *
 * Windows  :: Win32 everything ...
 * io       :: _read
 */


#define true 1
#define false 0


#define new(_type, _bytes) (_type)malloc(_bytes + 1)


enum types {
    t_char,
    t_str,
    t_int,
    t_long,
    t_double,
    t_float,
    t_unknown
};


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


#define str_add(...) _str_addva(__VA_ARGS__, NULL)
#define str_len(pointer) strlen(pointer);
int str_count(const char* string, const char* substr, int start, int end);
int str_eq(const char* a, const char* b);
int str_index(const char* str, const char* substr, int start, int end);
int str_isalpha(const char* string);
char* str_replace(const char* main, const char* repl, const char* with, int start, int end);
char* str_reverse(const char* string);
char* str_slice(const char* string, int start, int step, int end);
char** str_split(const char* a_str, char a_delim);
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


/* Generic Print
 * Copyright (C) 2021 Exebook
 */
int __print_enable_color = 1;
void __print_color(FILE* fd, int a) {
	if (!__print_enable_color) return;
	if (a == -1) fprintf(fd, "\033(B\033[m");
	else fprintf(fd, "\033[38;5;%im", a);
}

#define __print_array(fd, T, qual, color) \
	__print_color(fd, __print_color_normal); \
	int max_len = 16; \
	int n = size/sizeof(T); \
	T* m = va_arg(v, T*); \
	fprintf(fd, "["); \
	__print_color(fd, color); \
	for (int i = 0; i < (n < max_len ? n : max_len); i++) { \
		if (i > 0) fprintf(fd, " "); \
		fprintf(fd, qual, m[i]); \
	} \
	__print_color(fd, __print_color_normal); \
	if (n > max_len) fprintf(fd, "..."); \
	fprintf(fd, "]");




int __print_color_normal = -1; // -1 means default terminal foreground color
int __print_color_number = 4;
int __print_color_string = 1;
int __print_color_hex = 2;
int __print_color_float = 5;

void __print_setup_colors(int normal, int number, int string, int hex, int fractional) {
	__print_color_string = string;
	__print_color_number = number;
	__print_color_hex = hex;
	__print_color_normal = normal;
	__print_color_float = fractional;
}

void __print_func (FILE *fd, int count, unsigned short types[], ...) {
	va_list v;
	va_start(v, types);
	#ifdef __print_DEBUG
	fprintf(fd, "args[%i]: ", count);
	for (int i = 0; i < count; i++) {
		char type = types[i] & 0x1F;
		char size = types[i] >> 5;
		if (i > 0) fprintf(fd, " ");
		fprintf(fd, "%i[%i]", type, size);
	}
	fprintf(fd, "\n");
	#endif // __print_DEBUG

	for (int i = 0; i < count; i++) {
		if (i > 0) fprintf(fd, " ");
		char type = types[i] & 0x1F;
		char size = types[i] >> 5;
		if (type == 1) {
			__print_color(fd, __print_color_float);
			double d = va_arg(v, double);
			fprintf(fd, "%'G", d);
		}
		else if (type == 2) {
			__print_color(fd, __print_color_string);
			char c = va_arg(v, int);
			fprintf(fd, "'%c'", c); __print_color(fd, __print_color_number);
			fprintf(fd, "%i", (int)c);
		}
		else if (type == 3) {
			__print_color(fd, __print_color_number);
			char c = va_arg(v, int);
			fprintf(fd, "%i", (unsigned char)c);
			__print_color(fd, __print_color_normal);
			fprintf(fd, "<");
			__print_color(fd, __print_color_hex);
			fprintf(fd, "0x%X", (unsigned char)c);
			__print_color(fd, __print_color_normal);
			fprintf(fd, ">");
		}
		else if (type == 4) {
			__print_color(fd, __print_color_number);
			fprintf(fd, "%'i", va_arg(v, int));
		}
		else if (type == 5) {
			__print_color(fd, __print_color_number);
			fprintf(fd, "%'u", va_arg(v, int));
		}
		else if (type == 6) {
			__print_color(fd, __print_color_number);
			fprintf(fd, "%'li", va_arg(v, unsigned long));
		}
		else if (type == 7) {
			__print_color(fd, __print_color_number);
			fprintf(fd, "%'lu", va_arg(v, long));
		}
		else if (type == 8) {
			__print_color(fd, __print_color_string);
			fprintf(fd, "\"%s\"", va_arg(v, char*));
		}
		else if (type == 9) {
			__print_color(fd, __print_color_normal);
			fprintf(fd, "%s", va_arg(v, char*));
		}
		else if (type == 10) {
			__print_color(fd, __print_color_hex);
			fprintf(fd, "%p", va_arg(v, void*));
		}
		else if (type == 11) {
			__print_array(fd, int, "%i", __print_color_number);
		}
		else if (type == 12) {
			__print_array(fd, unsigned int, "%u", __print_color_number);
		}
		else if (type == 13) {
			__print_array(fd, short, "%i", __print_color_number);
		}
		else if (type == 14) {
			__print_array(fd, unsigned short, "%i", __print_color_number);
		}
		else if (type == 15) {
			__print_array(fd, char*, "\"%s\"", __print_color_string);
		}
		else {
			fprintf(fd, "print: unsupported type (of size %i)\n", size); break;
		}
	}
	va_end(v);
	__print_color(fd, -1);
	fprintf(fd, "\n");
}

#define __print_typeid(a) \
	__builtin_choose_expr(__print_is_type(a, double), 1, \
	__builtin_choose_expr(__print_is_type(a, float), 1, \
	__builtin_choose_expr(__print_is_type(a, char), 2, \
	__builtin_choose_expr(__print_is_type(a, unsigned char), 3, \
	__builtin_choose_expr(__print_is_type(a, int), 4, \
	__builtin_choose_expr(__print_is_type(a, unsigned int), 5, \
	__builtin_choose_expr(__print_is_type(a, long), 6, \
	__builtin_choose_expr(__print_is_type(a, unsigned long), 7, \
	__builtin_choose_expr(__print_is_type(a, short), 4, \
	__builtin_choose_expr(__print_is_type(a, char*), 8, \
	__builtin_choose_expr(__print_is_type(a, char[]), 9, \
	__builtin_choose_expr(__print_is_type(a, void*), 10, \
    __builtin_choose_expr(__print_is_type(a, double*), 11, \
	__builtin_choose_expr(__print_is_type(a, unsigned int[]), 12, \
	__builtin_choose_expr(__print_is_type(a, short[]), 13, \
	__builtin_choose_expr(__print_is_type(a, unsigned short[]), 14, \
	__builtin_choose_expr(__print_is_type(a, char*[]), 15, \
	__builtin_choose_expr(sizeof(a) == 1, 2, \
	__builtin_choose_expr(sizeof(a) == 2, 4, \
	(0)  )))))))))))))))))))
// in place of double[]
//__builtin_choose_expr(__print_is_type(a, double[]), 11, \
//	__builtin_choose_expr(__print_is_type(a, int[]), 11, 

#define __print_push(c,size,cont) (cont, *--_p = c | (size << 5))
#define __builtin_choose_expr __builtin_choose_expr
#define __print_is_type(a, t) __builtin_types_compatible_p(typeof(a), t)
#define __print_count_int(q,w,e,r,t,y,u,i,o,p,a,s,d,f,g,h,j,k,l,z,x,c,v,b,n,m,...) m
#define __print_count(a...)__print_count_int(a,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

#define __print_code(a, cont) __builtin_choose_expr(__print_is_type(a, void), 0, __print_push(__print_typeid(a), (sizeof(a)<(1<<16>>5)?sizeof(a):(1<<16>>5)-1), cont))

#define __print_types_int(q,w,e,r,t,y,u,i,o,p,a,s,d,f,g,h,j,k,l,z,x,c,v,b,n,m,...)__print_code(q,__print_code(w,__print_code(e,__print_code(r,__print_code(t,__print_code(y,__print_code(u,__print_code(i,__print_code(o,__print_code(p,__print_code(a,__print_code(s,__print_code(d,__print_code(f,__print_code(g,__print_code(h,__print_code(j,__print_code(k,__print_code(l,__print_code(z,__print_code(x,__print_code(c,__print_code(v,__print_code(b,__print_code(n,__print_code(m, 0))))))))))))))))))))))))))

#define __print_types(a...) __print_types_int(a, (void)0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)

#define fprint(fd, a...) ({ \
	int count = __print_count(a); \
	unsigned short stack[count], *_p = stack + count; \
	__print_types(a); \
	__print_func(fd, count, _p, a); \
})

#define print(a...) fprint(stdout, a)
