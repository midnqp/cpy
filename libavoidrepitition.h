#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>




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




#define typeof(var) _Generic(var,     	\
  int: 1, char: 2, char*: 3, long: 4,  	\
  double: 5, float: 6, default: 0)




#define len(arr) sizeof(arr)/sizeof(arr[0])




#define assert(expression) \
	(expression) ? printf(GRNBG "True" R0) : printf(REDBG "False" R0); \
	printf("\n");






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




char* int_str(int a) {
	// although, atoi() works fine!
	static char str[100000];
	sprintf(str, "%d", a);
	return str;
}




char*  substr(char* string, char* substr) {		
	static char noteCharMatched[1000000];	
	int i = 0;
	int j = 0;

	for(j = 0; j < strlen(string); j++) {
		if (substr[i] == string[j]) {
			strcat(noteCharMatched, &substr[i]);	// taking note since a %c matched
			i++;		// let's see if the next %c of substr matches with next %c of string. 
		}
		if (strcmp(noteCharMatched, substr)==0) { break; }
	}
	return noteCharMatched;
}




double sum(double numbers[], int arrlen) { 
  double sum = 0;
  for (int i=0; i < arrlen; i++) { 
    sum += numbers[i];
  } 
  return sum;
}




double max(double num, ...) {
	double max;
	va_list list;
	va_start(list, num);
	
	//max = va_arg(list, double);
	max = 0;
	// va_arg means: grab the next data_type.
	// var_arg(list, char) // grab the next char from the list
	for(double i=0; i<num; i++) {
		double nowD = va_arg(list, double);
		//int nowI = va_arg(list, int);
		printf("double: %lf \t int: %d\n", nowD, -1);

		if (nowD > max) { max = nowD; }
	}
	va_end(list);
	return max;
}
