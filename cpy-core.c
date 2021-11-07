#include "cpy.h"



// @deprecated
// use: linenoise.
char* input(const char* prompt) {
	char* tmp = new(char*, 10000); //10 KB
	strcpy(tmp, "");
	printf("%s", prompt); 
	fgets(tmp, 10000, stdin);
	
	size_t len = strlen(tmp);
	tmp = (char*)realloc(tmp, len);  
	tmp[len - 1] = '\0';  
	return tmp;
	// if allocation > input, realloc to save space
	// fgets adds a newline, while reading from stdin
}




/**
 * Unlike new(), var() takes semantic 
 * number of elements.
 *
 * @example
 * var(t_intlist, 10) - means 10 int in
 * the list.
 *
 * var(t_str, 100) - means a string
 * with length 10.
 */
void* var(int t_type, int n_items){
	if (t_type == t_str) {
		char* tmp = new(char*, n_items + 1);
		tmp[n_items + 1] = '\0';
		return tmp;
	}
	else if (t_type == t_numlist) {
		size_t alloc = sizeof(double) * n_items;
		double* numlist = new(double*, alloc);
		for (int i=0; i < n_items; i++) {
			numlist[i] = DBL_MAX;
		}
		return numlist;
	}
	print("CPY Runtime Error: Invalid t_type in \033[36mvoid* var(int t_type, int n_items)\033[0m");
	return new(void*, n_items);
}
