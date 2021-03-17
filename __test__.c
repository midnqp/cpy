/* This script tests and proves implementations. 
 *
 * Usage: 
 *     - Write the implementation test
 *     - Inside main(), add test in the list & invokation case.
 */
#include <stdio.h>
#include "libavoidrepetition.h"








void test_assert() {
	printf("--TESTING--\n");
	printf("--RESULT--\n");
	printf("Sorry! assert() can never pass string. See issue #8.\n");
}




void test_file_read() {
	printf("--TESTING--\n");
	char filename[100];
	printf("Filename: "); scanf("%s", filename);
	
	printf("--RESULT--\n");
	printf("%s", file_read(filename));
}




void test_max() {
	printf("--TESTING--\n");
	

	//create prompt & environment.
	

	printf("--RESULT--\n");
}




void test_min() {
	printf("--TESTING--\n");
	

	//create prompt & environment.
	

	printf("--RESULT--\n");
}




void test_substr() {
	printf("--TESTING substr()--\n");	
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
	strcpy(matched, substr(str, substring));
	printf("--RESULT--\n");
	printf("%s\n", matched);

	free(matched); free(substring); free(str);
}




void test_sum() {
	printf("--TESTING--\n");
	

	printf("Enter numbers (space-separated): ");
	char* input = (char*)malloc(sizeof(char) * 1024);;
	int i = 0;
	while(1) {
		scanf("%c", &input[i]);
		if (input[i] == '\n') {break;}
		else {i++;}
	}
	input[i] = '\0';
	for(i=0; i != '\0'; i++) {
		printf("%c", input[i]);
	}
	free(input);

	printf("--RESULT--\n");
}








int main() {	
	printf("----UNIT TESTING----\n\n");

	int u;			// unit number
	char implemented[20][128]=
	 {	
		"[1] assert(expression)        :: True | False",
		"[5] substr(str, substr)       :: substr (up to matched)",
		"[6] sum(array, len(array))    :: Sum of the array of numbers",
		"[8] max(array, len(array))    :: Item with the maximum value",
		"[9] min(array, len(array))    :: Item with the minimum value",
		"[10] file_read(filename)      :: Contents of the file",
	};

	
	int ic = 0;			//implementation counter
	while (strcmp(implemented[ic], "\0") != 0) {   // until we reach end of array
		printf("%s\n", implemented[ic]);
		ic++;
	}


	

	printf("\nUnit to test [integer]: "); scanf("%d", &u);
	printf("\n\n");

	/* The serial and numbering below means nothing
	 * great and intrinsic. It's just a list.
	 */
	switch(u)
	{
		case 1: test_assert(); break;
		case 5: test_substr(); break;
		case 6: test_sum(); break;
		case 8: test_max(); break;
		case 9: test_min(); break;
		case 10: test_file_read(); break;
		default: printf("The unit against the integer is not implemented.\n");
	}
	
	return 0;
}
