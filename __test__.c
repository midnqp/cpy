#include <stdio.h>
#include "lib-cpython-builtins.h"


void test_file_read() {printf("%s", file_read("README.md"));}




void test_list_max() {
}




void test_list_min() {
}




void test_str_substr() {
	char* str = (char*)malloc(1024); 
	*str = '\0';
	printf("String: "); 
	scanf("%s", str);
	strcat(str, "\0");
	
	char* substring = (char*)malloc(1024); 
	printf("Substring: ");
	scanf("%s", substring);
	strcat(substring, "\0");
	
	char *matched = (char*)malloc(1024);
	strcpy(matched, str_substr(str, substring));
	printf("--\n");
	printf("%s\n", matched);

	free(matched); free(substring); free(str);
}




void test_list_remove() {
	

void test_list_reverse(){}
void test_list_slice() {}
void test_list_sort(){}
void test_list_sum() {
	double numbers[] = {1, -1, 0.1, -0.1};
	printf("%lf", list_sum(numbers, 4));
}








int main() {	
	test_list_sum();
	return 0;
}
