#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>




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
#define REDBG  "\033[0;41m"
#define GRNBG  "\033[0;42m"




/* Given a variable name,
 * Returns the type.
 */
#define TYPE_INT     1
#define TYPE_CHAR    2
#define TYPE_STR     3
#define TYPE_LONG    4
#define TYPE_DOUBLE  5
#define TYPE_FLOAT   6
#define TYPE_UNKNOWN 0

#define type(var) _Generic(var, \
	int: TYPE_INT, char: TYPE_CHAR, char*: TYPE_STR, \
	long: TYPE_LONG, double: TYPE_DOUBLE, float: TYPE_FLOAT,\
	default: TYPE_UNKNOWN)




/* Given an int,
 * converts into string,
 * because atoi() leads to undefined behaviour.
 * Returns the string.
 */
char* str(void* data) {
	int t = type(data);    //input type
	
	if (t == TYPE_INT) {
		int val = *(int*)data;
		char* string = (char*)malloc(100000);
		sprintf(string, "%d", val);
		return string;	
	}
	else if (t == TYPE_STR) {
		char* val = (char*)data;
		return val;
	}
	char* unt = (char*)malloc(20);
	strcpy(unt, "UNKNOWN TYPE");
	return unt;
}




/* Given an array,
 * Returns the len of the array.
 */
#define len(arr) sizeof(arr)/sizeof(arr[0])




/* Given a C expression,
 * asserts it.
 */
#define assert(expression) \
	(expression) ? printf(GRNBG "True" R0) : printf(REDBG "False" R0); \
	printf("\n");




/* Given a filename,
 * reads a file. 
 * Returns the contents of the file.
 */
char* file_read(char* filename) {
		FILE *file = fopen(filename, "r");
		static char *fileContent;

		char ch;
		while (fscanf(file, "%c", &ch) == 1) {
				strcat(fileContent, &ch);
		}

		fclose(file);
		return fileContent;
}





/* Given a string, and a substring,
 * searches the substring in the string
 * Returns up to what is matched.
 */
char*  substr(char* string, char* substr) {		
	static char matched[1000000];	
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




/* Given an array of numbers, and len of the array,
 * determines the sum of the array
 * Returns the sum.
 */
double sum(double numbers[], int arrlen) { 
	double sum = 0;
	for (int i=0; i < arrlen; i++) { 
		sum += numbers[i];
	} 
	return sum;
}




/* Given an array of numbers, and length of the array,
 * determines the maximum value of the array
 * Returns the maximum item.
 */

double max (double numbers[], int arrlen) {
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

double min(double numbers[], int arrlen) {
	double minitem = numbers[0];
	for(int i=1; i < arrlen; i++) {
		if (numbers[i] < minitem) {
			minitem = numbers[i];
		}
	}
	return minitem;
}
