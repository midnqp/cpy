#ifndef H_STDIO
#include <stdio.h>
#endif

#ifndef H_LIBAR
#include "../libavoidrepitition.h"
#endif




void test_sum()
{
	printf("--TESTING--\n");
	

	printf("Enter numbers (space-separated): ");
	char* input = (char*)malloc(sizeof(char) * 1024);;
	char e;		//each char of input
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
	/*char* input = (char*)malloc(1024);
	char* ei[4];		// each input (array of strings)
	scanf("%s", input);

	char* e = strtok(input, " ");  //each n-th part of the split
	int i = 0;
	while(e != NULL) {
		ei[i++] = e;
		e = strtok(NULL, " ");
	}
	for (i = 0; i < 3; ++i) 
  	printf("%s\n", ei[i]);*/

	printf("--RESULT--\n");
}

