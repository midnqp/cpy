#include "cpy.h"
/*

char* input(const char* prompt) {
	char* tmp = new(char*, 10000); //10 KB
	strcpy(tmp, "");
	printf("%s", prompt); 
	fgets(tmp, 10000, stdin);
	
	size_t len = strlen(tmp);
	tmp = (char*)realloc(tmp, len);  
	tmp[len - 1] = '\0';  
	return tmp;
}*/
