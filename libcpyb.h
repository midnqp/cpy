#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdarg.h>




/* ANSI 3-bit and 4-bit color with escaped sequences.
 * According to specification, it produces 8 colors.
 * Later terminals started supporting background(BG) colors.
 */
#define R0     "\033[0;0m"
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




#define TYPE_CHAR    2
#define TYPE_STR     3
#define TYPE_INT     1
#define TYPE_LONG    4
#define TYPE_DOUBLE  5
#define TYPE_FLOAT   6
#define TYPE_UNKNOWN 0
//add more

// Given a variable name,
// Returns the type.
#define type(var) _Generic(var, \
	int: TYPE_INT, char: TYPE_CHAR, char*: TYPE_STR, \
	long: TYPE_LONG, double: TYPE_DOUBLE, float: TYPE_FLOAT,\
	default: TYPE_UNKNOWN)




/* Given a C expression,
 * asserts it.
 */
#include <assert.h>



/* Given a filename,
 * reads a file. 
 * Returns the contents of the file.
 */
//char file_read() {}
char* file_read(const char* filename) {
	FILE *file = fopen(filename, "r");
		
	//static char buffer[] = "";
	long length;
	if (file) {
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		char *buffer = (char*)malloc(length+1);
		fseek(file, 0, SEEK_SET);
		if (buffer) { fread(buffer, 1, length, file); }
		//fread(buffer, 1, length, file);
		fclose(file);

		return buffer;
	}
	else {perror("Error in reading file"); exit(1);}
}

long file_size(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (file) { 
		fseek(file, 0, SEEK_END);
		return ftell(file);
	}
	return -1;
}



/* Given a string
 * Converts to integer
 * Returns the integer.
 */
#define int(x) {(atoi(x); )}




// Given an array,
// Returns the len of the array.
#define list_len(arr) sizeof(arr)/sizeof(*arr)




// Given an array of numbers, and length of the array,
// determines the maximum value of the array
// Returns the maximum item.

double list_max (double numbers[], int arrlen) {
	double maxitem = numbers[0];
	for(int i=1; i<arrlen; i++) {
		if (numbers[i] > maxitem) {
			maxitem = numbers[i];
		}
	}
	return maxitem;
}




/* Given an array of numbers, and length of the array,
 * determines the minimum value of the array
 * Returns the minimum item.
 */

double list_min(double numbers[], int arrlen) {
	double minitem = numbers[0];
	for(int i=1; i < arrlen; i++) {
		if (numbers[i] < minitem) {
			minitem = numbers[i];
		}
	}
	return minitem;
}




double* list_remove(double numbers[], int arrlen, int tr, int occ) {
	// tr = to remove, occ = occureneces
	return numbers;
}




/* Given an array of numbers, and len of the array,
 * determines the sum of the array
 * Returns the sum.
 */
double list_sum(double numbers[], int arrlen) { 
	double sum = 0;
	for (int i=0; i < arrlen; i++) { sum += numbers[i];	} 
	return sum;
}



typedef struct string {
	char *str;
	size_t len;
	size_t lalloc; //last allocated size
} string;
void str_init(struct string string) {
	// String formalities.
	string.len = 0;
	string.str = (char*)malloc(string.len);
	string.str[0] = '\0';
}



//char *str_add(const char dest[], const char src[]) {
char *str_add(const char *dest, const char *src) {
	char *ret = (char*)malloc(strlen(dest) + strlen(src));
//	ret = (char*)"";
//	size_t totallen = 1 + strlen(dest) + strlen(src);
//	static char ret[] = "";
	
	strncat(ret, dest, strlen(dest));
	strncat(ret, src, strlen(src));
	
//	ret[totallen] = '\0';  //Not required for literals, but for arrays.
	return ret;
}

void str_addp(char *dest, const char *src) {
	// Adds *src after the *dest pointer.
	// Not returning.
	size_t totalLen = strlen(dest) + strlen(src) + 1;
	dest = (char*)realloc(dest, totalLen);
	strncat(dest, src, strlen(src)); 
	dest[strlen(dest)] = '\0';
}

char *_str_addva(const char *strings, ...);
void _str_addpva(char *dest, const char *strings, ...) {
	// Using va_args, adds multiple strings together.
	// ...to the *dest pointer. 
	// Doesn't return anything.

	va_list all;
	va_start(all, strings);

	char *parent = (char*)malloc(10000);
	char* tmp = (char*)malloc(1000);
	//strcpy(tmp, strings);
	tmp = (char*)strings;
	str_addp(dest, "-From str_addpva: The same scope-");
	int i =1;
	while (tmp != NULL) {
		str_addp(parent, tmp);
		printf("i: %-5d tmp: %-10s parent: %s\n", i, tmp, parent);
		tmp = va_arg(all, char*);
		i++;
	}
	str_addp(dest, parent);
	va_end(all);
	//free(&tmp);
}
#define str_addpva(...) _str_addpva(__VA_ARGS__, NULL)




char* _str_addva(const char *strings,... ) {
	// Using va_args, adds multiple strings (that are passed as arguments) together.
	// And, then returns.
	va_list allstrings;
	va_start(allstrings, strings);
	
	char *parent  = (char*)malloc(9000);
	char *tmp = (char*)malloc(500);
	tmp = (char*)strings;
	while (tmp != NULL) {
		str_addp(parent, tmp);
		tmp = va_arg(allstrings, char*);
	}
	va_end(allstrings);
	return parent;
}
#define str_addva(...) _str_addva(__VA_ARGS__, NULL)




/* Given a string, and a substring,
 * searches the substring in the string
 * Returns up to what is matched.
 */
char*  str_substr(char* string, char* substr) {		
	char* matched = (char*)malloc(strlen(substr));	
	size_t i = 0;    // counter for substr
	size_t j = 0;    // counter for string

	for(j = 0; j < strlen(string); j++) {
		if (substr[i] == string[j]) {
			strcat(matched, &substr[i]);    //substr[i] matched!
			i++; 
		}
		if (strcmp(matched, substr)==0) break;
	}
	return matched;
}




/* Given a string, substring, and starting position,
 * finds the substring
 * Returns the position of the substring.
 */
int str_index(char* str, char* substr, int start) {
	char string[strlen(str)];
	strncpy(string, str+start, strlen(str)-start);
	char *p = strstr(string, substr);
	if (p) { return p - (string+start); }
	return -1;
}




/*double sum(double count, ...) {
	va_list args;
	va_start(args, count);

	double sum=0;
	for (double i=0; i < count; i++)
		sum += va_arg(args, double);
	
	va_end(args);
	return sum;
}*/



//char* sys_out(char* command) {
//	FILE *cfp;
//	char output
//	return output;
//}
