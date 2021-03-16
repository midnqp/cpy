#ifndef H_STDIO
#include <stdio.h>
#endif

#ifndef H_LIBAR
#include "../libavoidrepitition.h"
#endif




void test_substr()
{
	

	printf("--TESTING substr()--\n");
	char* str = (char*)malloc(1024); printf("String: "); 
	scanf("%s", str);
	strcat(str, "\0");
	char* substring = (char*)malloc(1024); printf("Substring: "); 
	scanf("%s", substring);
	strcat(substring, "\0");
	
	char *matched = (char*)malloc(1024);
	strcpy(matched, substr(str, substring));
	printf("--RESULT--\n%s\n", matched);

	
}

