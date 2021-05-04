#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>




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




// Given an array,
// Returns the len of the array.
#define list_len(arr) sizeof(arr)/sizeof(*arr)




/* Given a C expression,
 * asserts it.
 */
#include <assert.h>



/* Given a filename,
 * reads a file. 
 * Returns the contents of the file.
 */
char* file_read(const char* filename) {
	FILE *file = fopen(filename, "r");
		
	char *buffer = 0;
	long length;
	if (file) {
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);
		buffer = (char*)malloc(length);
		if (buffer) { fread(buffer, 1, length, file); }
		fclose(file);
	}
	return buffer;
}



/* Given a string
 * Converts to integer
 * Returns the integer.
 */
#define int(x) {(atoi(x); )}




/* Given an array of numbers, and length of the array,
 * determines the maximum value of the array
 * Returns the maximum item.
 */

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
	char *
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




/* Given a string, and a substring,
 * searches the substring in the string
 * Returns up to what is matched.
 */
char*  str_substr(char* string, char* substr) {		
	char* matched = (char*)malloc(strlen(substr));	
	int i = 0;    // counter for substr
	int j = 0;    // counter for string

	for(j = 0; j < strlen(string); j++) {
		if (substr[i] == string[j]) {
			strcat(matched, &substr[i]);    //substr[i] matched!
			i++; 
		}
		if (strcmp(matched, substr)==0) { break; }
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




//char* sys_out(char* command) {
//	FILE *cfp;
//	char output
//	return output;
//}
