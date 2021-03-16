/* This script tests and proves implementations. 
 *
 * Usage: 
 *     - Write the implementation test, following __template__.h
 *     - Inside main(), add test in the list & invokation case.
 */

#include <stdio.h>
#define H_STDIO
#include "../libavoidrepitition.h"
#define H_LIBAR


int main() {	
	printf("----UNIT TESTING OF libavoidrepitition.h----\n\n");

	int u;			// unit number
	char implemented[20][128]=
	 {	
		"[1] assert(expression)        :: True | False",
		"[5] substr(str, substr)       :: substr (up to matched)",
		"[6] sum(array, len(array))    :: Sum of the array of numbers",
		"[8] max(array, len(array))    :: Item with the maximum value",
		"[9] min(array, len(array))    :: Item with the minimum value",	
	};

	
	int ic = 0;			//{implemented} counter
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
		default: printf("The unit against the integer is not implemented.\n");
	}
	
	return 0;
}
