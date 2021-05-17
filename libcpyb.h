/*
 * MIT License
 *
 * Copyright (c) 2021 Muhammad Bin Zafar <midnightquantumprogrammer@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include <stdlib.h> //malloc, realloc, exit
#include <string.h> //strcpy...
#include <stdio.h>  // printf, FILE, perror
#include <stdarg.h>  //va_list...
#include <sys/stat.h>  //mkdir


// ANSI 3-bit and 4-bit color with escaped sequences.
/* Commented because: doesn't work with str_addva()
#define R0     "\033[0;0m"   // COLOR RESET
#define BLK    "\033[0;30m"
#define RED    "\033[0;31m"
#define GRN    "\033[0;32m"
#define YLW    "\033[0;33m"
#define BLU    "\033[0;34m"
#define MGN    "\033[0;35m"
#define CYN    "\033[0;36m"
#define GRY    "\033[0;37m"
#define REDBG  "\033[0;41m"
#define GRNBG  "\033[0;42m"
#define MGNBG  "\033[0;45m"
#define GRYBG  "\033[0;47m"
*/


const char* R0=     "\033[0;0m";  // COLOR RESET
const char* BLK=    "\033[0;30m";	
const char* RED=    "\033[0;31m";
const char* GRN=    "\033[0;32m";
const char* YLW=    "\033[0;33m";
const char* BLU =   "\033[0;34m";
const char* MGN =   "\033[0;35m";
const char* CYN=    "\033[0;36m";
const char* GRY =   "\033[0;37m";
const char* REDBG=  "\033[0;41m";
const char* GRNBG=  "\033[0;42m";
const char* MGNBG=  "\033[0;45m";
const char* GRYBG=  "\033[0;47m";


#define TYPE_CHAR    2
#define TYPE_STR     3
#define TYPE_INT     1
#define TYPE_LONG    4
#define TYPE_DOUBLE  5
#define TYPE_FLOAT   6
#define TYPE_UNKNOWN 0


#define type(variable) _Generic(variable, \
	int: TYPE_INT, char: TYPE_CHAR, char*: TYPE_STR, \
	long: TYPE_LONG, double: TYPE_DOUBLE, float: TYPE_FLOAT,\
	default: TYPE_UNKNOWN)




#define new(type, bytes) ({ \
	char* __tempNew__ = (type)malloc(bytes); \
	strcpy(__tempNew__, ""); \
	__tempNew__; \
})
//#define new(type, bytes) (type)malloc(bytes);




char* file_read(const char* filename) {
	FILE *file = fopen(filename, "r");
	if (file) {
		fseek(file, 0, SEEK_END);
		long length = ftell(file);
		rewind(file);   
		//not using rewind was terrbile.
		// It kept reading weird characters after the file.
		// Not always, sometimes -- actual Undefined Behavior.
		char *buffer = (char*)malloc(length);
		fseek(file, 0, SEEK_SET);
		if (buffer) { fread(buffer, 1, length, file); }
		buffer[length] = '\0'; //fread doesn't automatically set that
		fclose(file);

		return buffer;
	}
	else {printf("Error in reading file: %s\n", filename); exit(1);}
}


long file_size(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (file) { 
		fseek(file, 0, SEEK_END);
		long size =ftell(file);
		fclose(file);
		return size;
	}
	fclose(file);
	return -1;
}


void file_write(const char* filename, const char* buffer) {
	FILE* f = fopen(filename, "w");
	if (f == NULL) {printf("Couldn't open file: %s\n", filename); exit(1);}
	fprintf(f, "%s", buffer);   //Not adding EOF - or something is wrong.
	//fwrite(buffer, 1, strlen(buffer), f);
	fclose(f);
}


void file_append(const char* filename, const char* buffer) {
	FILE* f = fopen(filename, "a");
	if (f == NULL) {printf("Couldn't open file: %s\n", filename); exit(1);}
	fprintf(f, "%s", buffer);
	fclose(f);
}




//#define int(x) {(atoi(x); )}


char* input() {
	char* tmp = new(char*, 10000); //10 KB
	fgets(tmp, 10000, stdin);
	size_t len =strlen(tmp);
	tmp = (char*)realloc(tmp, len);
	tmp[len-1] = '\0';  //fgets adds a newline, while reading from stdin.
	return tmp;
}




// Only works in the same scope.
#define list_len(arr) (sizeof(arr)/sizeof(*arr))




double list_max (double numbers[], int arrlen) {
	double maxitem = numbers[0];
	for(int i=1; i<arrlen; i++) {
		if (numbers[i] > maxitem) {
			maxitem = numbers[i];
		}
	}
	return maxitem;
}




double list_min(double numbers[], int arrlen) {
	double minitem = numbers[0];
	for(int i=1; i < arrlen; i++) {
		if (numbers[i] < minitem) {
			minitem = numbers[i];
		}
	}
	return minitem;
}




//double* list_remove(double numbers[], int arrlen, int tr, int occ) {
	// tr = to remove, occ = occureneces
//	return numbers;
//}




double list_sum(double numbers[], int arrlen) { 
	double sum = 0;
	for (int i=0; i < arrlen; i++) { sum += numbers[i];	} 
	return sum;
}







struct string {
	char *str;
	size_t len;
};

void str_init(struct string *string) {
	string->len = 0;
	string->str = (char*)malloc(string->len + 1);
	if (string->str == NULL) {printf("str_init() failed\n"); exit(1);}
	strcpy(string->str, "");
}


// Returns a pointer with *dest and *src concatenated.
char *str_add(const char *dest, const char *src) {
	size_t totalLen = strlen(dest) + strlen(src);
	char *ret = (char*)malloc(totalLen);
	
	strcpy(ret, dest);
	strcat(ret, src);
	
	return ret;
}

// Realloc, and Concatenate to *dest.
/*void str_addp(char *dest, const char *src) {
	// Adds *src after the *dest pointer.
	// Not returning.
	size_t totalLen = strlen(dest) + strlen(src);
	dest = (char*)realloc(dest, totalLen);
	strcat(dest, src); 
}*/

/*void _str_addpva(char *dest, const char *strings, ...) {
	// Using va_args, adds multiple strings together.
	// ...to the *dest pointer. 
	// Doesn't return anything.

	va_list all;
	va_start(all, strings);

	char *parent = (char*)malloc(10000);
	strcpy(parent, "");
	char* tmp = (char*)malloc(1000);
	strcpy(tmp, strings);
	while (tmp != NULL) {
		strcat(parent, tmp); 		
		tmp = va_arg(all, char*);
	}
	str_addp(dest, parent);
	va_end(all);
}
#define str_addpva(...) _str_addpva(__VA_ARGS__, NULL)
*/




char* _str_addva(const char *strings,... ) {
	// Using va_args, adds multiple strings (that are passed as arguments) together.
	// And, then returns.
	va_list allstrings;
	va_start(allstrings, strings);
	
	char *parent  = (char*)malloc(9000);
	strcpy(parent, "");
	char *tmp = (char*)malloc(5000);
	strcpy(tmp, "");
	strcpy(tmp, strings);

	while (tmp != NULL) {
		//str_addp(parent, tmp);
		strcat(parent, tmp);
		// strcat used. Because, str_addp() was causing "corrupted size vs prev_size"
		tmp = va_arg(allstrings, char*);
	}
	va_end(allstrings);
	return parent;
}
#define str_addva(...) _str_addva(__VA_ARGS__, NULL)




int str_eq(const char* a, const char* b) {
	if (strcmp(a, b)==0) return 1;
	else return 0;
}




/* Given a string, and a substring,
 * searches the substring in the string
 * Returns up to what is matched.
 */
char*  str_substr(char* string, char* substr) {		
	char* matched = (char*)malloc(strlen(substr));	
	strcpy(matched, "");
	size_t i = 0;    // counter for substr
	size_t j = 0;    // counter for string

	for(j = 0; j < strlen(string); j++) {
		if (substr[i] == string[j]) {
			strncat(matched, &substr[i], 1);    //substr[i] matched!
			i++; 
		}
		if (str_eq(matched, substr)) break;
	}
	return matched;
}




int str_index(const char* str, const char* substr, int headstart) {
	char* string = (char*)malloc( 100);  // temporary
	strncpy(string, str + headstart, strlen(str) - headstart);  //makes perfect sense
	char* p = strstr(string, substr);
	long int loc = (p - string)+headstart;
	if ((size_t)loc < strlen(str)) return loc;
	else return -1;
}





int str_count(const char* str, const char* substr, int headstart) {
	int i; 
	int count = 0;
	i = str_index(str, substr, headstart);
	while (i != -1) {
		count++;
		printf("%d\n", i);
		i = str_index(str, substr, i);
	}
	return count;
}




char* str_replace(const char* main, const char* repl, const char* with) {
	char* Result = new(char*, 1);
	int i = 0;
	int whereRepl = str_index(main, repl, 0);
	while (main[i] != '\0') {
		if (i >= whereRepl && whereRepl != -1) {
			// If 'i' is size_t, and 'whereRepl' is int,
			// then, although i > whereRepl, this condition is false!!!
			for (size_t j=0; j<strlen(with); j++)
				strncat(Result, &with[j], 1);
			whereRepl = str_index(main, repl, i+strlen(repl));
			i = i + strlen(repl);  //else block: main[i]
			//i = i + strlen(with);
			//printf("i == %d == whereRepl == %d\n", i, whereRepl);
		}
		else {
			strncat(Result, &main[i], 1);
			//printf("else: i++ is %d  whereRepl: %d\n", i, whereRepl);
			i++;
		}
		//printf("%s\n", Result);
		//printf("i: %zu  whereRepl: %d  string: %s\n", i, whereRepl, Result);
	}
	//printf("--%s--\n", Result);
	return Result;
}

