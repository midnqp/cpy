#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "cpy.h"
#undef str_put




void __str_put(char* var, char* value) {
	//free(var);
	strcpy(var, value);
	free(value);
}
#define str_put(...) __str_put(__VA_ARGS__)




int main() {
	char* line = new(char*, 100);
	strcpy(line, "");
	

	/* I have successfully reused a 
	 * pointer variable in C.
	 *
	 * Thank you!
	 */
	str_put(line, str_add(line, " - was a line."));
	printf("%s\n", line);

	free(line);
}
